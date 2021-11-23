#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "riscv.h"

/************** BEGIN HELPER FUNCTIONS PROVIDED FOR CONVENIENCE ***************/
const int R_TYPE = 0;
const int I_TYPE = 1;
const int MEM_TYPE = 2;
const int U_TYPE = 3;
const int UNKNOWN_TYPE = 4;

/**
 * Return the type of instruction for the given operation
 * Available options are R_TYPE, I_TYPE, MEM_TYPE, UNKNOWN_TYPE
 */
static int get_op_type(char *op)
{
    const char *r_type_op[] = {"add", "sub", "and", "or", "xor", "slt", "sll", "sra"};
    const char *i_type_op[] = {"addi", "andi", "ori", "xori", "slti"};
    const char *mem_type_op[] = {"lw", "lb", "sw", "sb"};
    const char *u_type_op[] = {"lui"};
    for (int i = 0; i < (int)(sizeof(r_type_op) / sizeof(char *)); i++)
    {
        if (strcmp(r_type_op[i], op) == 0)
        {
            return R_TYPE;
        }
    }
    for (int i = 0; i < (int)(sizeof(i_type_op) / sizeof(char *)); i++)
    {
        if (strcmp(i_type_op[i], op) == 0)
        {
            return I_TYPE;
        }
    }
    for (int i = 0; i < (int)(sizeof(mem_type_op) / sizeof(char *)); i++)
    {
        if (strcmp(mem_type_op[i], op) == 0)
        {
            return MEM_TYPE;
        }
    }
    for (int i = 0; i < (int)(sizeof(u_type_op) / sizeof(char *)); i++)
    {
        if (strcmp(u_type_op[i], op) == 0)
        {
            return U_TYPE;
        }
    }
    return UNKNOWN_TYPE;
}
/*************** END HELPER FUNCTIONS PROVIDED FOR CONVENIENCE ****************/

registers_t *registers;
// TODO: create any additional variables to store the state of the interpreter
hashtable_t *memory;

void init(registers_t *starting_registers)
{
    registers = starting_registers;
    // TODO: initialize any additional variables needed for state
    memory = ht_init(2000);
}

void end()
{
    // TODO: Free everything from memory
    ht_free(memory);
}

int operation(char *ope, int r1, int r2)
{
    printf(ope);
    const char *rth[] = {"add", "sub", "and", "or", "xor", "slt", "sll", "sra"};
    printf("%d", strcmp(ope, rth[0]));
    if (!strcmp(ope, rth[0]))
    {
        printf("we're here");
        return r1 + r2;
    }
    else
    {
        if (!strcmp(ope, rth[1]))
        {
            return r1 - r2;
        }
        else
        {
            if (!strcmp(ope, rth[2]))
            {
                return r1 & r2;
            }
            else
            {
                if (!strcmp(ope, rth[3]))
                {
                    return r1 | r2;
                }
                else
                {
                    if (!strcmp(ope, rth[4]))
                    {
                        return r1 ^ r2;
                    }
                    else
                    {
                        if (!strcmp(ope, rth[5]))
                        {
                            return r1 < r2; //fix
                        }
                        else
                        {
                            if (!strcmp(ope, rth[6]))
                            {
                                return r1 << r2;
                            }
                            else
                            {
                                if (!strcmp(ope, rth[7]))
                                {
                                    return r1 >> r2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
char *space_deleter(char *reg)
{ //debug
    // printf("start \n");
    // char *found;
    // while ((found = strsep(&reg, " ")) != NULL)
    // {
    //     strcat(reg, found);
    // }
    // printf("end \n");
    return reg;
}

// TODO: create any necessary helper functions
void r_type_helper(char *oper, char *instruct)
{

    // getting each register
    char *st_reg = strsep(&instruct, ",");
    char *temp = strsep(&st_reg, "x");
    char *reg1 = strsep(&instruct, ",");
    temp = strsep(&reg1, "x");
    char *reg2 = (strsep(&instruct, ","));
    temp = strsep(&reg2, "x");
    // registers into ints
    int *reg_st = &(registers->r[atoi(st_reg)]);
    int reg_1 = registers->r[atoi(reg1)];
    int reg_2 = registers->r[atoi(reg2)];

    *reg_st = operation(oper, reg_1, reg_2);
    printf("new value %d \n", *reg_st);
}

void i_type_helper(char *oper, char *instruct);

void step(char *instruction)
{
    // Extracts and returns the substring before the first space character,
    // by replacing the space character with a null-terminator.
    // `instruction` now points to the next character after the space
    // See `man strsep` for how this library function works
    char *op = strsep(&instruction, " ");
    // Uses the provided helper function to determine the type of instruction
    int op_type = get_op_type(op);
    // Skip this instruction if it is not in our supported set of instructions

    if (op_type == UNKNOWN_TYPE)
    {
        return;
    }
    else
    {
        if (op_type == R_TYPE)
        {

            r_type_helper(op, instruction);
        }
    }
    // TODO: write logic for evaluating instruction on current interpreter state
}
