# !/usr/bin/env python
# -*- encoding: utf-8 -*-
# generate_instance.py
# 2026-04-15
# xuwei <lewis.xuwei@outlook.com>

import random
import copy
from typing import Dict, List
import json
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle


class Building:

    def __init__(self, building_id, left_coord, bottom_coord, width, length, rent_cost):
        self.building_id: int = building_id
        self.left_coord: int = left_coord
        self.bottom_coord: int = bottom_coord
        self.width: int = width
        self.length: int = length
        self.rent_cost: float = rent_cost

    def __str__(self):
        return "Building {0} {1} {2} {3} {4} {5}".format(
            self.building_id,
            self.left_coord,
            self.bottom_coord,
            self.width,
            self.length,
            self.rent_cost,
        )


class Workflow:

    def __init__(self, source_id, target_id, quantity):
        self.source_id: int = source_id
        self.target_id: int = target_id
        self.quantity: int = quantity


class Task:

    def __init__(self, task_id, width, length):
        self.task_id: int = task_id
        self.width: int = width
        self.length: int = length
        self.workflow: Dict[int, Workflow] = {}

        # For plotting figures
        self.left: int = 0
        self.bottom: int = 0

    def add_workflow(self, source_id, target_id, quantity):
        self.workflow[target_id] = Workflow(
            source_id=source_id, target_id=target_id, quantity=quantity
        )

    def set_coordination(self, left, bottom):
        self.left = left
        self.bottom = bottom


class InstanceGenerator:
    MAP_WIDTH_MAX = 1000
    BUILDING_WIDTH_MAX = 200
    BUILDING_WIDTH_MIN = 100
    BUILDING_LEGNTH_MAX = 200
    BUILDING_LEGNTH_MIN = 100
    PADDING_MAX = 200
    PADDING_MIN = 100
    TASK_WIDTH_MAX = 70
    TASK_WIDTH_MIN = 30
    TASK_LENGTH_MAX = 60
    TASK_LENGTH_MIN = 20
    WORKFLOW_MAX = 20
    WORKFLOW_MIN = 10
    NUM_LAYER_MAX = 5
    NUM_LAYER_MIN = 1
    CONNECT_PROB = 0.3

    def __init__(self, num_buildings, num_tasks):
        self.num_buildings: int = num_buildings
        self.num_tasks: int = num_tasks
        self.buildings: Dict[int, Building] = {}
        self.tasks: Dict[int, Task] = {}
        self.layers: List[List[int]] = []

    def generate_buildings(self):
        self.buildings = {}

        left_coord = 0.0
        bottom_coord = 0.0
        max_length = 0
        t = 0
        while t < self.num_buildings:
            width = random.randint(self.BUILDING_WIDTH_MIN, self.BUILDING_WIDTH_MAX)
            length = random.randint(self.BUILDING_LEGNTH_MIN, self.BUILDING_LEGNTH_MAX)

            assert (
                0 < width < self.MAP_WIDTH_MAX
            ), "The width of building cannot beyond `MAP_WIDTH_MAX`"

            assert length > 0, "The length of building cannot be negative"

            # new line of builings
            if left_coord + width > self.MAP_WIDTH_MAX:
                vertical_padding = random.randint(self.PADDING_MIN, self.PADDING_MAX)
                print(
                    "new line for building {} with vertical padding {}".format(
                        t, vertical_padding
                    )
                )
                left_coord = random.randint(self.PADDING_MIN, self.PADDING_MAX)
                bottom_coord = bottom_coord + max_length + vertical_padding
                max_length = vertical_padding + length

            vertical_padding = random.randint(0, self.PADDING_MIN)
            print(bottom_coord, vertical_padding)
            max_length = max(max_length, vertical_padding + length)
            print(max_length)
            self.buildings[t] = Building(
                building_id=t,
                left_coord=left_coord,
                bottom_coord=bottom_coord + vertical_padding,
                width=width,
                length=length,
                rent_cost=int(0.1 * (width * length) * (1.05 - 0.1 * random.random())),
            )
            print(self.buildings[t])
            horizontal_padding = random.randint(self.PADDING_MIN, self.PADDING_MAX)
            left_coord = left_coord + width + horizontal_padding

            t = t + 1

    def generate_workflows(self):
        self.tasks = {}
        self.layers = []

        # Generate all task nodes
        for task_id in range(self.num_tasks):
            width = random.randint(self.TASK_WIDTH_MIN, self.TASK_WIDTH_MAX)
            length = random.randint(self.TASK_LENGTH_MIN, self.TASK_LENGTH_MAX)
            self.tasks[task_id] = Task(task_id=task_id, width=width, length=length)

        task_list = list(self.tasks.keys())
        random.shuffle(task_list)

        print("--------------------------------------")
        kappa = random.randint(3, 7)
        kappa = min(len(task_list), kappa)
        prev_layer = task_list[0:kappa]
        task_list = task_list[kappa:]
        self.layers.append(prev_layer)
        while len(task_list) > 0:
            kappa = random.randint(self.NUM_LAYER_MIN, self.NUM_LAYER_MAX)
            kappa = min(len(task_list), kappa)
            next_layer = task_list[0:kappa]
            task_list = task_list[kappa:]
            self.layers.append(next_layer)

            for source in prev_layer:
                for target in next_layer:
                    quantity = 0
                    if random.random() < self.CONNECT_PROB:
                        quantity = random.randint(self.WORKFLOW_MIN, self.WORKFLOW_MAX)
                        self.tasks[source].add_workflow(
                            source_id=source, target_id=target, quantity=quantity
                        )
                        print(
                            "add new task link {} -> {}: {}".format(
                                source, target, quantity
                            )
                        )
                # if some nodes are not connected, randomly select a node from `next_layer`
                if len(self.tasks[source].workflow) == 0:
                    quantity = random.randint(self.WORKFLOW_MIN, self.WORKFLOW_MAX)
                    target = random.choice(next_layer)
                    self.tasks[source].add_workflow(
                        source_id=source, target_id=target, quantity=quantity
                    )
                    print(
                        "add new task link {} -> {}: {}".format(
                            source, target, quantity
                        )
                    )

            prev_layer = next_layer
            print("--------------------------------------")

    def write_to_file(self, filename):
        json_object = {"buildings": [], "task_nodes": [], "workflow": []}

        for _, building in self.buildings.items():
            json_object["buildings"].append(
                {
                    "id": building.building_id,
                    "x": building.left_coord,
                    "y": building.bottom_coord,
                    "w": building.width,
                    "h": building.length,
                    "c": building.rent_cost,
                }
            )

        for _, task_node in self.tasks.items():
            json_object["task_nodes"].append(
                {
                    "id": task_node.task_id,
                    "x": task_node.left,
                    "y": task_node.bottom,
                    "w": task_node.width,
                    "h": task_node.length,
                }
            )

            for _, workflow in task_node.workflow.items():
                json_object["workflow"].append(
                    {
                        "source": workflow.source_id,
                        "target": workflow.target_id,
                        "quantity": workflow.quantity,
                    }
                )
        with open(filename, "w") as jsonfile:
            json.dump(json_object, jsonfile, indent=4)

    def plot_buildings(self):
        # define Matplotlib figure and axis
        fig, ax = plt.subplots()
        most_right = max(
            self.buildings,
            key=lambda k: self.buildings[k].left_coord + self.buildings[k].width,
        )
        xlim = self.buildings[most_right].left_coord + self.buildings[most_right].width
        most_top = max(
            self.buildings,
            key=lambda k: self.buildings[k].bottom_coord + self.buildings[k].length,
        )
        ylim = self.buildings[most_top].bottom_coord + self.buildings[most_top].length
        # add rectangle to plot
        padding = 20
        ax.set_xlim(left=-padding, right=xlim + padding)
        ax.set_ylim(top=ylim + padding, bottom=-padding)
        for _, building in self.buildings.items():
            # building.building_id
            ax.add_patch(
                Rectangle(
                    xy=(building.left_coord, building.bottom_coord),
                    width=building.width,
                    height=building.length,
                    edgecolor="black",
                    facecolor="white",
                    fill=True,
                    lw=1,
                )
            )

        # displayplot
        plt.show()

    def fix_nodes_coord(self):
        left_coord = 0
        length = 200
        width = 400
        for nlayer in range(len(self.layers)):
            bottom_coord = 0
            for i in range(len(self.layers[nlayer])):
                task_id = self.layers[nlayer][i]
                self.tasks[task_id].set_coordination(
                    left=left_coord, bottom=bottom_coord
                )
                bottom_coord += length

            left_coord += width

    def fix_nodes_last_layer_zero_degree(self):
        # Fix the nodes with zero degree in the last layer
        unconnected_tasks = copy.deepcopy(self.layers[-1])
        for target in unconnected_tasks:
            for source in self.layers[-2]:
                if target in self.tasks[source].workflow:
                    unconnected_tasks.remove(target)
                    break

        for target in unconnected_tasks:
            source = random.choice(self.layers[-2])
            quantity = random.randint(self.WORKFLOW_MIN, self.WORKFLOW_MAX)
            self.tasks[source].add_workflow(
                source_id=source, target_id=target, quantity=quantity
            )


if __name__ == "__main__":
    # random.seed(1)
    generator = InstanceGenerator(num_buildings=2, num_tasks=10)
    generator.generate_buildings()
    generator.generate_workflows()
    generator.fix_nodes_last_layer_zero_degree()
    generator.fix_nodes_coord()
    generator.plot_buildings()
    generator.write_to_file("test1.json")
