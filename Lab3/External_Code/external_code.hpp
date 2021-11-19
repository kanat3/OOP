#pragma once
#include "vect.hpp"

const int MAX_POINTS = 20;
void print_coords (const vector::vec a, int size);
int x_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4);
int y_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4);
void clip(int poly_points[][2], int &poly_size,
          int x1, int y1, int x2, int y2);
void suthHodgClip(int poly_points[][2], int poly_size,
                  int clipper_points[][2], int clipper_size);
int is_clockwise_order (const int x1, const int y1, const int x2, const int y2);
void check_polygon (const vector::vec& a, const int size);
void _clip(vector::vec& poly_points, int& poly_size,
                  int x1, int y1, int x2, int y2);
void _suthHodgClip(vector::vec poly_points, int poly_size,
                  vector::vec clipper_points, int clipper_size);
void dialog (void);
void test_coords (void);