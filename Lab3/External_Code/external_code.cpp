#include "external_code.hpp"
#include <iostream>
#include "vect.hpp"
#include "toolib.hpp"

void print_coords (const vector::vec a, int size) {
    for (int i = 0; i < size*COORD_SYSTEM; i += 2) {
        std::cout << '(' << a[i] <<
                ", " << a[i + 1] << ") ";
    }
    std::cout << std::endl;
}

int x_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4) {
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

int y_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4) {
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

void clip(int poly_points[][2], int &poly_size,
          int x1, int y1, int x2, int y2) {
    int new_points[MAX_POINTS][2], new_poly_size = 0;
    for (int i = 0; i < poly_size; i++) {
        int k = (i+1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);
        if (i_pos < 0  && k_pos < 0) {
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        } else if (i_pos >= 0  && k_pos < 0) {
            new_points[new_poly_size][0] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        } else if (i_pos < 0  && k_pos >= 0) {
            new_points[new_poly_size][0] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
        else {
        }
    }
    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++) {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}

void suthHodgClip(int poly_points[][2], int poly_size,
                  int clipper_points[][2], int clipper_size) {
    puts("\nfirst_version");
    for (int i = 0; i < clipper_size; i++) {
        int k = (i + 1) % clipper_size;
        clip(poly_points, poly_size, clipper_points[i][0],
             clipper_points[i][1], clipper_points[k][0],
             clipper_points[k][1]);
    }

    for (int i = 0; i < poly_size; i++) {
        std::cout << '(' << poly_points[i][0] <<
                ", " << poly_points[i][1] << ") ";
    }
    std::cout << std::endl;
}

int is_clockwise_order (const int x1, const int y1, const int x2, const int y2) {
    if ((x2 - x1)*(y2 + y1) >= 0 ) {
        return 0;
    } else {
        return 1;
    }
}

void check_polygon (const vector::vec& a, const int size) {
    int clockwise = 0;
    for (int i = 0; i < size/2; i++) {
        clockwise = is_clockwise_order(a[i], a[i+1], a[i+2], a[i+3]);
        if (clockwise == 1) {
            throw std::invalid_argument("Not clockwise order");
        }
    }
    return;
}

void _clip(vector::vec& poly_points, int& poly_size,
                  int x1, int y1, int x2, int y2) {
    int new_points[MAX_POINTS][2], new_poly_size = 0;
    vector::vec new_poly_points(MAX_POINTS, 0);
    int k;
    int j = 0;
    for (int i = 0; i < poly_size*COORD_SYSTEM; i += 2) {
        if (i + 2 != poly_size*COORD_SYSTEM) {
            k = i + 2;
        } else {
            k = 0;
        }
        int ix = poly_points[i], iy = poly_points[i + 1];
        int kx = poly_points[k], ky = poly_points[k + 1];
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);
        if (i_pos < 0  && k_pos < 0) {
            new_poly_points[j] = kx;
            new_poly_points[j + 1] = ky;
            j += 2;
            new_poly_size++;
        } else if (i_pos >= 0  && k_pos < 0) {
            new_poly_points[j] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_points[j + 1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            j += 2;
            new_poly_points[j] = kx;
            new_poly_points[j + 1] = ky;
            j += 2;
            new_poly_size += 2;
        } else if (i_pos < 0  && k_pos >= 0) {
            new_poly_points[j] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_points[j + 1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            j += 2;
            new_poly_size++;
        }
    }
    poly_size = new_poly_size;
    poly_points = new_poly_points;
}

void _suthHodgClip(vector::vec poly_points, int poly_size,
                  vector::vec clipper_points, int clipper_size) {
    puts("\nmy_version");
    int k = 0;
    for (int i = 0; i < clipper_size*COORD_SYSTEM; i += 2) {
        if (i + 2 != clipper_size*COORD_SYSTEM) {
            k = i + 2;
        } else {
            k = 0;
        }
        _clip(poly_points, poly_size, clipper_points[i],
             clipper_points[i + 1], clipper_points[k],
             clipper_points[k + 1]);
    }
    for (int i = 0; i < poly_size*COORD_SYSTEM; i += 2) {
        std::cout << '(' << poly_points[i] <<
                ", " << poly_points[i + 1] << ") ";
    }
    std::cout << std::endl;

}

void dialog (void) {
    puts("======== This program implements the Sutherland - Hodgman algorithm ========");
    puts("Enter the polygon. For example (100,150), (200,250), (300,200)");
    int poly_size;
    getEl(poly_size, std::cin);
    vector::vec poly_array(COORD_SYSTEM*poly_size, 0);
    for (int i = 0; i < poly_size*COORD_SYSTEM; i += 2) {
        std::cout << std::endl << "Enter x: ";
        getEl(poly_array[i], std::cin);
        std::cout << "Enter y: ";
        getEl(poly_array[i + 1], std::cin);
        std::cout << std::endl;
    }
    puts("Enter the clipping area. For example (150,150), (150,200), (200,200), (200,150)");
    int clipper_size;
    getEl(clipper_size, std::cin);
    vector::vec clipper_array(COORD_SYSTEM*clipper_size, 0);
    for (int i = 0; i < clipper_size*COORD_SYSTEM; i += 2) {
        std::cout << std::endl << "Enter x: ";
        getEl(clipper_array[i], std::cin);
        std::cout << "Enter y: ";
        getEl(clipper_array[i + 1], std::cin);
        std::cout << std::endl;
    }
    puts("You entered:");
    puts("\nPolygon:");
    print_coords(poly_array, poly_size);
    puts("\nClipping area:");
    print_coords(clipper_array, clipper_size);

    /***************************************************/
    /************* Algorithm *****************/
    check_polygon(poly_array, poly_size*COORD_SYSTEM);
    check_polygon(clipper_array, clipper_size*COORD_SYSTEM);
    _suthHodgClip(poly_array, poly_size, clipper_array,
                 clipper_size);
}

void test_coords (void) {
    int poly_size = 3;
    vector::vec poly_array(COORD_SYSTEM*poly_size, 0);
    poly_array[0] = 100;
    poly_array[1] = 150;
    poly_array[2] = 200;
    poly_array[3] = 250;
    poly_array[4] = 300;
    poly_array[5] = 200;

    check_polygon(poly_array, poly_size*COORD_SYSTEM);

    int poly_points[poly_size][COORD_SYSTEM] = {{100,150}, {200,250},
                              {300,200}};

    int clipper_size = 4;
    vector::vec clipper_array(COORD_SYSTEM*clipper_size, 0);
    clipper_array[0] = 150;
    clipper_array[1] = 150;
    clipper_array[2] = 150;
    clipper_array[3] = 200;
    clipper_array[4] = 200;
    clipper_array[5] = 200;
    clipper_array[6] = 200;
    clipper_array[7] = 150;
    /*clipper_array[0] = 151;
    clipper_array[1] = 152;
    clipper_array[2] = 153;
    clipper_array[3] = 204;
    clipper_array[4] = 205;
    clipper_array[5] = 206;
    clipper_array[6] = 207;
    clipper_array[7] = 158;*/


    check_polygon(clipper_array, clipper_size*COORD_SYSTEM);

    int clipper_points[clipper_size][COORD_SYSTEM] = {{150,150}, {150,200},
                              {200,200}, {200,150} };
    /*int clipper_points[clipper_size][COORD_SYSTEM] = {{151,152}, {153,204},
                              {205,206}, {207,158} };*/

    suthHodgClip(poly_points, poly_size, clipper_points,
                 clipper_size);
    _suthHodgClip(poly_array, poly_size, clipper_array,
                 clipper_size);
}