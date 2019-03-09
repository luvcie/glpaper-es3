/*
 *  Copyright (C) 2019 Scoopta
 *  This file is part of GLPaper
 *  GLPaper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GLPaper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GLPaper.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map.h>
#include <paper.h>
#include <stdio.h>
#include <stdint.h>

static void print_usage(char** argv) {
	char* slash = strrchr(argv[0], '/');
	uint64_t offset;
	if(slash == NULL) {
		offset = 0;
	} else {
		offset = (slash - argv[0]) + 1;
	}
	printf("%s [options] <output> <shader>\n", argv[0] + offset);
	printf("Options:\n");
	printf("--help\t-h\tDisplays this help message\n");
	printf("--fps\t-f\tSets the FPS to render at\n");
	exit(0);
}

static struct map* parse_args(int argc, char** argv) {
	struct map* ret = map_init();
	struct map* abrev = map_init();
	map_put(abrev, "f", "fps");
	if(argc > 1) {
		for(uint8_t count = 1; count < argc; ++count) {
			if(strcmp(argv[count], "-h") == 0 || strcmp(argv[count], "--help") == 0) {
				print_usage(argv);
			} else {
				if(strncmp(argv[count], "--", 2) == 0) {
					map_put(ret, argv[count] + 2, argv[count + 1]);
					++count;
				} else if(strncmp(argv[count], "-", 1) == 0) {
					for(uint8_t chr = 1; chr < strlen(argv[count]); ++chr) {
						char str[2] = {argv[count][chr], 0};
						map_put(ret, map_get(abrev, str), argv[++count]);
					}
				} else {
					if(count + 1 >= argc) {
						print_usage(argv);
					}
					map_put(ret, "_output", argv[count++]);
					map_put(ret, "_shader", argv[count]);
				}
			}
		}
	} else {
		print_usage(argv);
	}
	return ret;
}

int main(int argc, char** argv) {
	struct map* args = parse_args(argc, argv);
	if(argc > 2) {
		char* fpsStr = map_get(args, "fps");
		uint16_t fps;
		if(fpsStr == NULL) {
			fps = 0;
		} else {
			fps = strtol(fpsStr, NULL, 10);
		}
		paper_init(map_get(args, "_output"), map_get(args, "_shader"), fps);
	} else {
		print_usage(argv);
	}
}
