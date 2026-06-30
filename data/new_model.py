from pyscipopt import Model
import json

json_file = open("data/test1.json")
data = json.load(json_file)

T = len(data["buildings"])
N = len(data["task_nodes"])
F = len(data["workflow"])

scip = Model()
p = [scip.addVar(vtype="B", lb=0, ub=1, name="p_{}".format(t)) for t in range(T)]
x = [scip.addVar(vtype="C", lb=0, ub=None, name="x_{}".format(i)) for i in range(N)]
y = [scip.addVar(vtype="C", lb=0, ub=None, name="y_{}".format(i)) for i in range(N)]
r = [scip.addVar(vtype="B", lb=0, ub=1, name="r_{}".format(i)) for i in range(N)]
z = [
    [scip.addVar(vtype="B", lb=0, ub=1, name="z_{}_{}".format(i, t)) for t in range(T)]
    for i in range(N)
]
l = [
    [scip.addVar(vtype="B", lb=0, ub=1, name="l_{}_{}".format(i, j)) for j in range(N)]
    for i in range(N)
]
m = [
    [scip.addVar(vtype="B", lb=0, ub=1, name="m_{}_{}".format(i, j)) for j in range(N)]
    for i in range(N)
]
d = [
    [
        scip.addVar(vtype="C", lb=0, ub=None, name="d_{}_{}".format(i, j))
        for j in range(N)
    ]
    for i in range(N)
]
a = [
    [
        scip.addVar(vtype="C", lb=0, ub=None, name="a_{}_{}".format(i, j))
        for j in range(N)
    ]
    for i in range(N)
]
b = [
    [
        scip.addVar(vtype="C", lb=0, ub=None, name="b_{}_{}".format(i, j))
        for j in range(N)
    ]
    for i in range(N)
]


###############################################################
obj = 0
for t in range(T):
    obj += data["buildings"][t]["c"] * p[t]

for workflow in data["workflow"]:
    i = workflow["source"]
    j = workflow["target"]
    obj += workflow["quantity"] * d[i][j]
scip.setObjective(obj, sense="minimize")

###############################################################
for i in range(N):
    expr = 0
    for t in range(T):
        expr += z[i][t]
    scip.addCons(expr >= 1)

for i in range(N):
    for t in range(T):
        scip.addCons(z[i][t] <= p[t])

for workflow in data["workflow"]:
    i = workflow["source"]
    j = workflow["target"]
    w_i = data["task_nodes"][i]["w"]
    w_j = data["task_nodes"][j]["w"]
    h_i = data["task_nodes"][i]["h"]
    h_j = data["task_nodes"][j]["h"]
    scip.addCons(d[i][j] == a[i][j] + b[i][j])
    scip.addCons(
        a[i][j]
        >= (x[i] + 0.5 * w_i * (1 - r[i]) + 0.5 * h_i * r[i])
        - (x[j] + 0.5 * w_j * (1 - r[j]) + 0.5 * h_j * r[j])
    )
    scip.addCons(
        a[i][j]
        >= (x[j] + 0.5 * w_j * (1 - r[j]) + 0.5 * h_j * r[j])
        - (x[i] + 0.5 * w_i * (1 - r[i]) + 0.5 * h_i * r[i])
    )
    scip.addCons(
        b[i][j]
        >= (y[i] + 0.5 * h_i * (1 - r[i]) + 0.5 * w_i * r[i])
        - (y[j] + 0.5 * h_j * (1 - r[j]) + 0.5 * w_j * r[j])
    )
    scip.addCons(
        b[i][j]
        >= (y[j] + 0.5 * h_j * (1 - r[j]) + 0.5 * w_j * r[j])
        - (y[i] + 0.5 * h_i * (1 - r[i]) + 0.5 * w_i * r[i])
    )

for t in range(T):
    for j in range(N):
        for i in range(j):
            scip.addCons(
                l[i][j] + l[j][i] + m[i][j] + m[j][i] + (1 - z[i][t]) + (1 - z[j][t])
                >= 1
            )

for j in range(N):
    for i in range(N):
        scip.addCons(
            x[i]
            + data["task_nodes"][i]["w"] * (1 - r[i])
            + data["task_nodes"][i]["h"] * r[i]
            <= x[j] + 1000000 * (1 - l[i][j])
        )
        scip.addCons(
            y[i]
            + data["task_nodes"][i]["h"] * (1 - r[i])
            + data["task_nodes"][i]["w"] * r[i]
            <= y[j] + 1000000 * (1 - m[i][j])
        )

for t in range(T):
    for i in range(N):
        scip.addCons(
            x[i]
            + data["task_nodes"][i]["w"] * (1 - r[i])
            + data["task_nodes"][i]["h"] * r[i]
            <= data["buildings"][t]["x"]
            + data["buildings"][t]["w"]
            + 1000000 * (1 - z[i][t])
        )
        scip.addCons(x[i] >= data["buildings"][t]["x"] - 1000000 * (1 - z[i][t]))

        scip.addCons(
            y[i]
            + data["task_nodes"][i]["h"] * (1 - r[i])
            + data["task_nodes"][i]["w"] * r[i]
            <= data["buildings"][t]["y"]
            + data["buildings"][t]["h"]
            + 1000000 * (1 - z[i][t])
        )
        scip.addCons(y[i] >= data["buildings"][t]["y"] - 1000000 * (1 - z[i][t]))


scip.writeProblem(filename="example_file.lp", trans=False, genericnames=False)
scip.setParam("parallel/minnthreads", 12)
scip.setParam("parallel/maxnthreads", 12)
scip.optimize()

for t in range(T):
    if scip.getVal(p[t]) == 1:
        print("building {} is used.".format(t))

for t in range(T):
    for i in range(N):
        if scip.getVal(z[i][t]) == 1:
            print("tasknode {} is placed on building {}.".format(i, t))

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

fig, ax = plt.subplots()
ax.set_xlim(left=-0, right=800)
ax.set_ylim(top=250, bottom=0)
for t in range(T):
    ax.add_patch(
        Rectangle(
            (data["buildings"][t]["x"], data["buildings"][t]["y"]),
            data["buildings"][t]["w"],
            data["buildings"][t]["h"],
            edgecolor="black",
        )
    )
for i in range(N):
    print("{} {} {}".format(scip.getVal(x[i]), scip.getVal(y[i]), scip.getVal(r[i])))
    if scip.getVal(r[i]) == 1:
        ax.add_patch(
            Rectangle(
                (
                    scip.getVal(x[i]),
                    scip.getVal(y[i]),
                ),
                data["task_nodes"][i]["h"],
                data["task_nodes"][i]["w"],
                edgecolor="pink",
            )
        )
    else:
        ax.add_patch(
            Rectangle(
                (
                    scip.getVal(x[i]),
                    scip.getVal(y[i]),
                ),
                data["task_nodes"][i]["w"],
                data["task_nodes"][i]["h"],
                edgecolor="pink",
            )
        )

plt.show()
