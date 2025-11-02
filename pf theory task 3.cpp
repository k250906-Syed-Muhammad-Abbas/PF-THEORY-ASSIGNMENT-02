#include <stdio.h>
#include <stdlib.h>

#define POWER_ON 0
#define OVERLOAD 1
#define MAINTENANCE 2
#define MAX_SIZE 10

int set_flag(int sector, int flag)
{
    return sector | (1 << flag);
}

int clear_flag(int sector, int flag)
{
    return sector & ~(1 << flag);
}

int check_flag(int sector, int flag)
{
    return (sector >> flag) & 1;
}

void convert_to_upper(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        i++;
    }
}

void update_sector_status(int **grid, int row, int col)
{
    int choice;
    printf("\n1. POWER ON/OFF\t\t2. OVERLOAD WARNING\t\t3. MAINTENANCE REQUIRED\n");
    printf("CHOOSE STATUS TO UPDATE: \t\t");
    scanf("%d", &choice);

    char action[10];
    if (choice == 1)
    {
        printf("TURN POWER ON OR OFF? \t\t");
        scanf("%s", action);
        convert_to_upper(action);
        if (action[0] == 'O' && action[1] == 'N')
            grid[row][col] = set_flag(grid[row][col], POWER_ON);
        else
            grid[row][col] = clear_flag(grid[row][col], POWER_ON);
    }
    if (choice == 2)
    {
        printf("SET OR CLEAR OVERLOAD? \t\t");
        scanf("%s", action);
        convert_to_upper(action);
        if (action[0] == 'S')
            grid[row][col] = set_flag(grid[row][col], OVERLOAD);
        else
            grid[row][col] = clear_flag(grid[row][col], OVERLOAD);
    }
    if (choice == 3)
    {
        printf("SET OR CLEAR MAINTENANCE? \t\t");
        scanf("%s", action);
        convert_to_upper(action);
        if (action[0] == 'S')
            grid[row][col] = set_flag(grid[row][col], MAINTENANCE);
        else
            grid[row][col] = clear_flag(grid[row][col], MAINTENANCE);
    }
}

void print_sector_symbol(int sector)
{
    if (check_flag(sector, POWER_ON))
        printf("ON");
    else
        printf("__");

    if (check_flag(sector, OVERLOAD))
        printf("?");
    else
        printf("_");

    if (check_flag(sector, MAINTENANCE))
        printf("??");
    else
        printf("_");
}

void display_grid(int **grid, int rows, int cols)
{
    printf("\n===== GRID STATUS =====\n");
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            print_sector_symbol(grid[i][j]);
            printf("\t\t");
        }
        printf("\n");
    }
    printf("=======================\n");
    printf("LEGEND:\n");
    printf("ON = POWER ON\t\t? = DANGER/OVERLOAD\t\t?? = MAINTENANCE REQUIRED\n");
    printf("__ = POWER OFF\t\t_ = NORMAL/NO WARNING\t\t_ = NO MAINTENANCE\n");
}

void query_sector_status(int **grid, int row, int col)
{
    int sector = grid[row][col];
    printf("\nSECTOR (%d,%d) REPORT:\n", row, col);
    printf("POWER: %s\t\t", check_flag(sector, POWER_ON) ? "ON" : "OFF");
    printf("OVERLOAD: %s\t\t", check_flag(sector, OVERLOAD) ? "YES" : "NO");
    printf("MAINTENANCE: %s\n", check_flag(sector, MAINTENANCE) ? "YES" : "NO");
}

void run_system_diagnostic(int **grid, int rows, int cols)
{
    int overloaded = 0;
    int maintenance_needed = 0;
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            overloaded += check_flag(grid[i][j], OVERLOAD);
            maintenance_needed += check_flag(grid[i][j], MAINTENANCE);
        }
    }
    printf("\n=== SYSTEM DIAGNOSTIC ===\n");
    printf("OVERLOADED SECTORS: %d\t\tSECTORS NEEDING MAINTENANCE: %d\n", overloaded, maintenance_needed);
}

int main()
{
    int rows;
    int cols;
    printf("ROWS IN GRID (1 TO %d): \t\t", MAX_SIZE);
    scanf("%d", &rows);
    while (rows < 1 || rows > MAX_SIZE)
    {
        printf("INVALID INPUT! ENTER ROWS BETWEEN 1 AND %d: \t\t", MAX_SIZE);
        scanf("%d", &rows);
    }

    printf("COLUMNS IN GRID (1 TO %d): \t\t", MAX_SIZE);
    scanf("%d", &cols);
    while (cols < 1 || cols > MAX_SIZE)
    {
        printf("INVALID INPUT! ENTER COLUMNS BETWEEN 1 AND %d: \t\t", MAX_SIZE);
        scanf("%d", &cols);
    }

    int **grid = (int**)malloc(rows * sizeof(int*));
    int i;
    for (i = 0; i < rows; i++)
        grid[i] = (int*)calloc(cols, sizeof(int));

    int choice;
    while (1)
    {
        display_grid(grid, rows, cols);
        printf("\n1. UPDATE SECTOR\t\t2. QUERY SECTOR\t\t3. SYSTEM DIAGNOSTIC\t\t4. EXIT\n");
        printf("YOUR CHOICE: \t\t");
        scanf("%d", &choice);

        int r, c;
        if (choice == 1)
        {
            printf("ENTER ROW NUMBER (0 TO %d): \t\t", rows - 1);
            scanf("%d", &r);
            while (r < 0 || r >= rows)
            {
                printf("INVALID ROW! ENTER ROW BETWEEN 0 AND %d: \t\t", rows - 1);
                scanf("%d", &r);
            }

            printf("ENTER COLUMN NUMBER (0 TO %d): \t\t", cols - 1);
            scanf("%d", &c);
            while (c < 0 || c >= cols)
            {
                printf("INVALID COLUMN! ENTER COLUMN BETWEEN 0 AND %d: \t\t", cols - 1);
                scanf("%d", &c);
            }
            update_sector_status(grid, r, c);
        }

        if (choice == 2)
        {
            printf("ENTER ROW NUMBER (0 TO %d): \t\t", rows - 1);
            scanf("%d", &r);
            while (r < 0 || r >= rows)
            {
                printf("INVALID ROW! ENTER ROW BETWEEN 0 AND %d: \t\t", rows - 1);
                scanf("%d", &r);
            }

            printf("ENTER COLUMN NUMBER (0 TO %d): \t\t", cols - 1);
            scanf("%d", &c);
            while (c < 0 || c >= cols)
            {
                printf("INVALID COLUMN! ENTER COLUMN BETWEEN 0 AND %d: \t\t", cols - 1);
                scanf("%d", &c);
            }
            query_sector_status(grid, r, c);
        }

        if (choice == 3)
            run_system_diagnostic(grid, rows, cols);

        if (choice == 4)
        {
            printf("GOODBYE!\n");
            break;
        }

        if (choice < 1 || choice > 4)
            printf("TRY AGAIN!\n");
    }

    for (i = 0; i < rows; i++)
        free(grid[i]);
    free(grid);

    return 0;
}

