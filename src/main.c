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

#include <paper.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>

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
	printf("--fork\t-F\tForks glpaper so you can close the terminal\n");
	printf("--fps\t-f\tSets the FPS to render at\n");
	printf("--layer\t-l\tSpecifies layer to run on\n");
	exit(0);
}

int main(int argc, char** argv) {
	if(argc > 2) {
		struct option opts[] = {
			{
				.name = "help",
				.has_arg = no_argument,
				.flag = NULL,
				.val = 'h'
			},
			{
				.name = "fork",
				.has_arg = no_argument,
				.flag = NULL,
				.val = 'F'
			},
			{
				.name = "fps",
				.has_arg = required_argument,
				.flag = NULL,
				.val = 'f'
			},
			{
				.name = "layer",
				.has_arg = required_argument,
				.flag = NULL,
				.val = 'l'
			},
			{
				.name = NULL,
				.has_arg = 0,
				.flag = NULL,
				.val = 0
			}
		};
		char* fpsStr = NULL;
		char* layer = NULL;
		char opt;
		while((opt = getopt_long(argc, argv, "hFf:l:", opts, NULL)) != -1) {
			switch(opt) {
			case 'h':
				print_usage(argv);
				break;
			case 'F':
				if(fork() > 0) {
					exit(0);
				}
				break;
			case 'f':
				fpsStr = optarg;
				break;
			case 'l':
				layer = optarg;
				break;
			}
		}
		uint16_t fps;
		if(fpsStr == NULL) {
			fps = 0;
		} else {
			fps = strtol(fpsStr, NULL, 10);
		}
		paper_init(argv[optind], argv[optind + 1], fps, layer);
	} else {
		print_usage(argv);
	}
}
