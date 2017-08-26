#! /usr/bin/python3

import sys
import random
import queue
from math import sin

from termcolor import colored


def paint_round(color, map, cols, rows, pos, max_size):
    x = pos % cols
    y = pos // cols
    offsets = [-1, 0, 1]
    q = queue.Queue()
    q.put([x, y])
    size = random.randint(0, max_size)
    nb_to_paint = sum([pow(4, i) for i in range(size)])
    while nb_to_paint > 0:
        t = q.get()
        if t[1] < rows and t[0] < cols:
            map[t[1]][t[0]] = color
        nb_to_paint -= 1
        for i in offsets:
            for j in offsets:
                if i != j:
                    q.put([x + i, y + j])


def paint_round_sappling(map, omap, cols, rows, pos, max_size):
    x = pos % cols
    y = pos // cols
    offsets = [-1, 0, 1]
    q = queue.Queue()
    q.put([x, y])
    size = random.randint(0, max_size)
    nb_to_paint = sum([pow(4, i) for i in range(size)])
    while nb_to_paint > 0:
        t = q.get()
        if t[1] < rows and t[0] < cols:
            if map[t[1]][t[0]] == 0:
                omap[t[1]][t[0]] = 1
            elif map[t[1]][t[0]] == 4:
                omap[t[1]][t[0]] = 2
        nb_to_paint -= 1
        for i in offsets:
            for j in offsets:
                if i != j:
                    q.put([x + i, y + j])


def paint_round_ore(map, omap, cols, rows, pos, max_size):
    x = pos % cols
    y = pos // cols
    offsets = [-1, 0, 1]
    q = queue.Queue()
    q.put([x, y])
    size = random.randint(0, max_size)
    nb_to_paint = sum([pow(4, i) for i in range(size)])
    while nb_to_paint > 0:
        t = q.get()
        if t[1] < rows and t[0] < cols and map[t[1]][t[0]] != 1:
            omap[t[1]][t[0]] = 3
        nb_to_paint -= 1
        for i in offsets:
            for j in offsets:
                if i != j:
                    q.put([x + i, y + j])


def paint_round_mountains(color, map, cols, rows, pos, max_size):
    x = pos % cols
    y = pos // cols
    offsets = [-1, 0, 1]
    q = queue.Queue()
    q.put([x, y])
    size = random.randint(0, max_size)
    nb_to_paint = sum([pow(4, i) for i in range(size)])
    while nb_to_paint > 0:
        t = q.get()
        if t[1] < rows and t[0] < cols:
            if random.randint(0, 4) == 0:
                map[t[1]][t[0]] = 4
            else:
                map[t[1]][t[0]] = color
        nb_to_paint -= 1
        for i in offsets:
            for j in offsets:
                if i != j:
                    q.put([x + i, y + j])


def print_map_colored(map):
    s = ""
    for line in map:
        for elt in line:
            t = None
            if elt == 1:
                t = colored(str(elt), 'green')
            elif elt == 2:
                t = colored(str(elt), 'white')
            elif elt == 3:
                t = colored(str(elt), 'cyan')
            elif elt == 0:
                t = colored(str(elt), 'grey')
            s += t
        s += "\n"
    print(s)


def compute_heights(map, hmap, rows, cols):
    for y in range(rows):
        offset = float(random.randint(0, 10) * 0.1)
        for x in range(cols):
            h = int(sin(float(x / 4) + offset) * 5)
            if h > 0 and map[y][x] != 1:
                hmap[y][x] = h
    for x in range(cols):
        offset = float(random.randint(0, 10) * 0.1)
        for y in range(rows):
            h = int(sin(float(y / 4) + offset) * 5)
            if h > 0 and map[y][x] != 1:
                hmap[y][x] = h
    """
    size = rows * cols
    nb_pit_points = size // 6
    pit_point_max_size = 6
    for _ in range(nb_pit_points):
        pos = random.randint(0, size)
        paint_round(0, hmap, cols, rows, pos, pit_point_max_size)
    """

def print_map(map):
    s = ""
    for line in map:
        for elt in line:
            s += str(elt) + " "
        s += "\n"
    print(s)


def main():
    cols = int(sys.argv[1])
    rows = int(sys.argv[2])
    size = cols * rows
    map = [[1 for _ in range(cols)] for _ in range(rows)]
    nb_grass_points = size // 6
    nb_sand_points = size // 6
    nb_rock_points = size // 6
    nb_snow_points = size // 6
    grass_point_max_size = 6
    for _ in range(nb_sand_points):
        pos = random.randint(0, size)
        paint_round(2, map, cols, rows, pos, grass_point_max_size)
    for _ in range(nb_rock_points):
        pos = random.randint(0, size)
        paint_round(3, map, cols, rows, pos, grass_point_max_size)
    for _ in range(nb_snow_points):
        pos = random.randint(0, size)
        paint_round(4, map, cols, rows, pos, grass_point_max_size)
    for _ in range(nb_grass_points):
        pos = random.randint(0, size)
        paint_round(0, map, cols, rows, pos, grass_point_max_size)
    hmap = [[0 for _ in range(cols)] for _ in range(rows)]
    compute_heights(map, hmap, rows, cols)
    for y in range(rows):
        for x in range(cols):
            if map[y][x] != 1 and hmap[y][x] == 0:
                hmap[y][x] = 1
            if map[y][x] == 3 and hmap[y][x] < 2:
                hmap[y][x] = 2
    omap = [[0 for _ in range(cols)] for _ in range(rows)]
    nb_sappling_points = size // 8
    sappling_point_max_size = 4
    for _ in range(nb_sappling_points):
        pos = random.randint(0, size)
        paint_round_sappling(map, omap, cols, rows, pos, sappling_point_max_size)
    nb_ore_points = size // 16
    ore_point_max_size = 3
    for _ in range(nb_ore_points):
        pos = random.randint(0, size)
        paint_round_ore(map, omap, cols, rows, pos, ore_point_max_size)
    print(str(cols) + " " + str(rows))
    print_map(map)
    print_map(hmap)
    print_map(omap)


if __name__ == "__main__":
    main()
