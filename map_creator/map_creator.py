#! /usr/bin/python3

import sys
import random
import queue

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
    map = [[3 for _ in range(cols)] for _ in range(rows)]
    nb_grass_points = size // 3
    grass_point_max_size = 6
    for _ in range(nb_grass_points):
        pos = random.randint(0, size)
        paint_round(0, map, cols, rows, pos, grass_point_max_size)
    nb_forest_points = size // 24
    forest_point_max_size = 4
    for _ in range(nb_forest_points):
        pos = random.randint(0, size)
        paint_round(1, map, cols, rows, pos, forest_point_max_size)
    nb_mountains_points = size // 28
    mountains_point_max_size = 6
    for _ in range(nb_mountains_points):
        pos = random.randint(0, size)
        paint_round_mountains(2, map, cols, rows, pos, mountains_point_max_size)
    placed = False
    cn = 25
    while cn > 0:
        i = random.randint(0, rows - 1)
        j = random.randint(0, cols - 1)
        if map[i][j] == 0:
            map[i][j] = 5
            cn -= 1
    print(str(cols) + " " + str(rows))
    print_map(map)


if __name__ == "__main__":
    main()
