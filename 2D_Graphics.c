#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 25
#define COLS 60

char canvas[ROWS][COLS];

/* ---------------- Initialize Canvas ---------------- */
void initCanvas() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            canvas[i][j] = ' ';
}

/* ---------------- Display Canvas ---------------- */
void display() {
    system("clear || cls"); // Clears console screen dynamically
    
    // Top Border
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("|"); // Left Border
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n"); // Right Border
    }

    // Bottom Border
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");
}

/* ---------------- Draw Line ---------------- */
void drawLine(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int steps = dx > dy ? dx : dy;

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        // FIXED: Boundary check applied
        if ((int)x >= 0 && (int)x < ROWS && (int)y >= 0 && (int)y < COLS)
            canvas[(int)x][(int)y] = ch;

        x += xInc * (x1 < x2 ? 1 : -1); // Bug fix for negative direction lines
        y += yInc * (y1 < y2 ? 1 : -1);
    }
}

/* ---------------- Draw Rectangle ---------------- */
void drawRectangle(int r, int c, int h, int w, char ch) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            // FIXED: Boundary safety logic added
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                if (i == r || i == r + h - 1 || j == c || j == c + w - 1)
                    canvas[i][j] = ch;
            }
        }
    }
}

/* ---------------- Draw Circle ---------------- */
void drawCircle(int cx, int cy, int radius, char ch) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // FIXED: Multiplying row distance to compensate for tall terminal characters
            float rowDiff = (i - cx) * 2.0; 
            float colDiff = (j - cy);
            float dist = (rowDiff * rowDiff) + (colDiff * colDiff);
            float r2 = radius * radius;

            // FIXED: Draws a hollow frame outline instead of solid filling
            if (dist >= r2 - radius && dist <= r2 + radius) {
                canvas[i][j] = ch;
            }
        }
    }
}

/* ---------------- Draw Triangle ---------------- */
void drawTriangle(int r, int c, int height, char ch) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= i; j++) {
            if (r + i < ROWS && c + j < COLS && r + i >= 0)
                canvas[r + i][c + j] = ch;
            if (r + i < ROWS && c - j >= 0 && r + i >= 0)
                canvas[r + i][c - j] = ch;
        }
    }
}

/* ---------------- Clear Area (Delete Object) ---------------- */
void clearArea(int r, int c, int h, int w) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
                canvas[i][j] = ' ';
        }
    }
}

/* ---------------- Menu ---------------- */
void menu() {
    int choice;

    while (1) {
        printf("\n--- 2D GRAPHICS MENU ---\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Delete Object (Clear Area)\n");
        printf("6. Modify Rectangle\n");
        printf("7. Clear Entire Screen\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break; // Safety clear on bad input

        if (choice == 1) {
            int x1, y1, x2, y2;
            printf("Enter row1 col1 row2 col2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            drawLine(x1, y1, x2, y2, '*');
        }
        else if (choice == 2) {
            int r, c, h, w;
            printf("Enter row col height width: ");
            scanf("%d%d%d%d", &r, &c, &h, &w);
            drawRectangle(r, c, h, w, '#');
        }
        else if (choice == 3) {
            int x, y, r;
            printf("Enter center row col and radius: ");
            scanf("%d%d%d", &x, &y, &r);
            drawCircle(x, y, r, 'o');
        }
        else if (choice == 4) {
            int r, c, h;
            printf("Enter top-vertex row col height: ");
            scanf("%d%d%d", &r, &c, &h);
            drawTriangle(r, c, h, '+');
        }
        // FIXED: Implemented Menu Options for deletion & modification mapping
        else if (choice == 5) {
            int r, c, h, w;
            printf("Enter area layout to wipe (row col height width): ");
            scanf("%d%d%d%d", &r, &c, &h, &w);
            clearArea(r, c, h, w);
        }
        else if (choice == 6) {
            int r, c, h, w;
            char newCh;
            printf("Enter target rectangle coordinates (row col height width): ");
            scanf("%d%d%d%d", &r, &c, &h, &w);
            printf("Enter new symbol character: ");
            scanf(" %c", &newCh);
            clearArea(r, c, h, w);
            drawRectangle(r, c, h, w, newCh);
        }
        else if (choice == 7) {
            initCanvas();
        }
        else if (choice == 8) {
            break;
        }

        display();
    }
}

/* ---------------- MAIN ---------------- */
int main() {
    initCanvas();
    menu();
    return 0;
}