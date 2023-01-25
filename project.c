/**
 * Include File
 * @brief includes
**/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/**
 * @file project.c
 * @file regs.txt
 * @file in.txt
 * @brief final project
 * @date 1401/11/04
 * @author mahta-rd
 * @note 
 * Please do not copy 
 * @warning 
 * WARNING!
 * \mainpage description of our project
 * This project is about the registers
*/
/**
 * @brief global values
**/
/**32 registers*/
int S[32]; /**conditional registers*/
int conregs[8]; /**something like ram that we can save our values in it*/
int stack[50];
/**
 * Function parityflag
 * @brief for conditional register 0
 * @param[in] int
 * @return void
**/
void parityflag(int calc)
{
    int count = 0;
    while (calc > 0)
    {
        if (calc % 2 == 1)
        {
            count++;
        }
        calc /= 2;
    }
    if (count % 2 == 1)
    {
        conregs[0] = 1;
    }
    else
    {
        conregs[0] = 0;
    }
}
/**
 * Function zeroflag
 * @brief for conditional register 1 when the calculation's answer is zero.
 * @param[in] int
 * @return void
**/
void zeroflag(int calc)
{
    if (calc == 0)
    {
        conregs[1] == 1;
    }
    else
    {
        conregs[1] == 0;
    }
}
/**
 * Function signflag
 * @brief for conditional register 2 when the calculation's answer is negative.
 * @param[in] int
 * @return void
**/
void signflag(int calc)
{
    if (calc < 0)
    {
        conregs[2] = 1;
    }
    else
    {
        conregs[2] = 0;
    }
}
/**
 * Function overflowflag for add, sub & mull calculations.
 * @brief for conditional register 5 when we have overflow
 * @param[in] int
 * @return void
**/
void overflowflag_ADD(int value1, int value2, int add)
{
    if (0 < value1 && 0 < value2 && add < 0 || value1 < 0 && value2 < 0 && 0 < add)
    {
        conregs[5] = 1;
    }
    else
    {
        conregs[5] = 0;
    }
}

void overflowflag_SUB(int value1, int value2, int sub)
{
    if (0 > value1 && 0 < value2 && sub > 0 || value1 > 0 && value2 < 0 && 0 > sub)
    {
        conregs[5] = 1;
    }
    else
    {
        conregs[5] = 0;
    }
}

void overflowflag_MULL(int value1, int value2, int mull)
{
    if (value1 != 0 && (mull / value1) != value2)
    {
        conregs[5] = 1;
    }
    else
    {
        conregs[5] = 0;
    }
}
/**
 * Function red 
 * @brief for better outputs in redcolor
 * @param[in] void
 * @return void
**/
void red()
{
    printf("\033[1;31m");
}
/**
 * Function green 
 * @brief for better outputs in greencolor
 * @param[in] void
 * @return void
**/
void green()
{
    printf("\033[1;32m");
}
/**
 * Function yellow 
 * @brief for better outputs in yellowcolor
 * @param[in] void
 * @return void
**/
void yellow()
{
    printf("\033[1;33m");
}
/**
 * Function blue
 * @brief for better outputs in bluecolor
 * @param[in] void
 * @return void
**/
void blue()
{
    printf("\033[1;34m");
}
/**
 * Function purple 
 * @brief for better outputs in purplecolor
 * @param[in] void
 * @return void
**/
void purple()
{
    printf("\033[1;35m");
}
/**
 * Function reset 
 * @brief it resets color to original state
 * @param[in] void
 * @return void
**/
void reset()
{
    printf("\033[1;0m");
}
/**
 * Function ADD
 * @brief for adding two registers & put the result in the other register
 * @param[in] int (integer number rd, rs & rt)
 * @return void
**/
void ADD(int rd, int rs, int rt)
{
    S[rd] = S[rs] + S[rt];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
    overflowflag_ADD(S[rs], S[rt], S[rd]);
}
/**
 * Function SUB
 * @brief for subing two registers & put the result in the other register
 * @param[in] int (integer number rd, rs & rt)
 * @return void
**/
void SUB(int rd, int rs, int rt)
{
    S[rd] = S[rt] - S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
    overflowflag_SUB(S[rs], S[rt], S[rd]);
}
/**
 * Function AND
 * @brief this function AND two registers & put the result in the other register
 * @param[in] int (integer number rd, rs & rt)
 * @return void
**/
void AND(int rd, int rs, int rt)
{
    S[rd] = S[rt] & S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}
/**
 * Function XOR
 * @brief this function XOR two registers & put the result in the other register
 * @param[in] int (integer number rd, rs & rt)
 * @return void
**/
void XOR(int rd, int rs, int rt)
{
    S[rd] = S[rt] ^ S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}
/**
 * Function OR
 * @brief this function OR two registers & put the result in the other register
 * @param[in] int (integer number rd, rs & rt)
 * @return void
**/
void OR(int rd, int rs, int rt)
{
    S[rd] = S[rt] | S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}
/**
 * Function ADDI
 * @brief for adding a registers and a number & put the result in the other register
 * @param[in] int (integer number rt, rs & Imm)
 * @return void
**/
void ADDI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] + Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
    overflowflag_ADD(S[rs], Imm, S[rt]);
}
/**
 * Function SUBI
 * @brief for subbing a registers and a number & put the result in the other register
 * @param[in] int (integer number rt, rs & Imm)
 * @return void
**/
void SUBI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] - Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
    overflowflag_SUB(S[rs], Imm, S[rt]);
}
/**
 * Function ANDI
 * @brief this function AND a register with a number & put the result in the other register
 * @param[in] int (integer number rt, rs & Imm)
 * @return void
**/
void ANDI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] & Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}
/**
 * Function XORI
 * @brief this function XOR a register with a number & put the result in the other register
 * @param[in] int (integer number rt, rs & Imm)
 * @return void
**/
void XORI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] ^ Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}
/**
 * Function ORI
 * @brief this function OR a register with a number & put the result in the other register
 * @param[in] int (integer number rt, rs & Imm)
 * @return void
**/
void ORI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] | Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}
/**
 * Function MOV
 * @brief this function puts a number or value of a register in other register
 * @param[in] int (integer number rt & Imm)
 * @return void
**/
void MOV(int rt, int Imm)
{
    S[rt] = Imm;
}
/**
 * Function SWP
 * @brief this function swap two registers
 * @param[in] int (integer number rt & rs)
 * @return void
**/
void SWP(int rt, int rs)
{
    int t;
    t = S[rt];
    S[rt] = S[rs];
    S[rs] = t;
}
/**
 * Function DUMP_REGS
 * @brief this function prints the value of all registers with all conditional registers
 * @param[in] void
 * @return void
**/
void DUMP_REGS()
{
    green();
    printf("Registers:\n");
    blue();
    for (int i = 0; i < 32; i++)
    {
        printf("%d, ", S[i]);
    }
    yellow();
    printf("\nConditional Registers:\n");
    purple();
    for (int j = 0; j < 8; j++)
    {
        printf("%d, ", conregs[j]);
    }
    reset();
}
/**
 * Function DUMP_REGS_F
 * @brief this function saves the print the value of all registers with all conditional registers in a file in the name of regs.tx
 * @param[in] void
 * @return void
**/
void DUMP_REGS_F()
{
    FILE *file;
    file = fopen("regs.txt", "w");
    if (file == NULL)
    {
        red();
        printf("\nERROR!\n");
        reset();
    }
    else
    {
        fprintf(file, "Registers:\n");
        for (int j = 0; j < 32; j++)
        {
            fprintf(file, "%d, ", S[j]);
        }
        fprintf(file, "\nConditional Registers:\n");
        for (int i = 0; i < 8; i++)
        {
            fprintf(file, "%d, ", conregs[i]);
        }
    }
    fclose(file);
}
/**
 * Function INPUT
 * @brief this function gets value for register 0
 * @param[in] void
 * @return void
**/
void INPUT()
{
    scanf("%d", &S[0]);
}
/**
 * Function OUTPUT
 * @brief this function prints the value of register 0
 * @param[in] void
 * @return void
**/
void OUTPUT()
{
    blue();
    printf("\n%d\n", S[0]);
    reset();
}
/**
 * Function DIV
 * @brief this function divides two registers and puts the quotient in register rt & the remain in register rs
 * @param[in] int (integer number rs & rt)
 * @return void
**/
void DIV(int rt, int rs)
{
    int quot;
    quot = S[rt] / S[rs];
    S[rs] = S[rt] % S[rs];
    S[rt] = quot;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}
/**
 * Function MULL
 * @brief in this function we multiply two registers and put the 4 more valuable bits in register rt & the 4 less valuable bits in register rs
 * @param[in] int (integer number rs & rt)
 * @return void
**/
void MULL(int rt, int rs)
{
    int mult;
    mult = S[rt] * S[rs];
    overflowflag_MULL(S[rt], S[rs], mult);
    // S[rt] = mult >> 4;
    // S[rs] = mult << 4;
    // S[rs] = mult & 15;
    // S[rt] = mult & 240;
    S[rt] = mult / 16;
    S[rs] = mult % 16;
    parityflag(mult);
    zeroflag(mult);
    signflag(mult);
}
/**
 * Function PUSH
 * @brief in this function we push all stacks and save our value in stack 0
 * @param[in] int (integer number rs)
 * @return void
**/
void PUSH(int rs)
{
    for (int i = 0; i < 50; i++)
    {
        stack[i + 1] = stack[i];
    }
    stack[0] = S[rs];
}
/**
 * Function POP
 * @brief in this function we empty stack 0 and pull up all the stacks
 * @param[in] int (integer number rt)
 * @return void
**/
void POP(int rt)
{
    S[rt] = stack[0];
    for (int i = 0; i < 50; i++)
    {
        stack[i] = stack[i + 1];
    }
}
/**
 * Function IndexError
 * @brief this function checks the errors for negative index of registers & the index which is more than 31 because there isn't such a register
 * @param[in] int and char (integer number result, value & value1 and array orders)
 * @return int (number 1 or 0)
**/
int IndexError(int result, int value, int value1, char orders[14])
{
    int flag = 0;
    if (result < 0 || value < 0 || value1 < 0)
    {
        red();
        printf("\nERROR in %s! The Index is negative.\n", orders);
        reset();
        flag = 1;
    }
    if (31 < result || 31 < value || 31 < value1)
    {
        red();
        printf("\nERROR in %s! The index is more than 31.\n", orders);
        reset();
        flag = 1;
    }
    if (flag != 1)
    {
        return 1;
    }
    return 0;
}
/**
 * function main
 * \section main function
 * @brief this function do whatever is written in a file which user gives to us
 * @param[in] int and char* (integer number argc and array argv)
 * @return int (number 0)
 * \subsection (int argc counts the characters in argv, char *argv a pointer which points to whatever user gives to us and put that in one of its array)
**/
int main(int argc, char *argv[])
{
    int flag, linecheck = 0, k;
    FILE *Main;
    /**
     * @code we get the name of a file which the commands are in from user if user doesn't give the name of the file or the file is empty we open file in.txt*/
    if (argc < 2)
    {
        Main = fopen("in.txt", "r");
    }
    else
    {
        Main = fopen(argv[1], "r");
    }
    char line[1000];
    int value, value1, result, countjmp = 0;
    /**
     * @code we count the lines of command in the file
    */
    while (fscanf(Main, "%[^\n]\n", line) != EOF)
    {
        linecheck++;
    }
    rewind(Main);
    /**
     * @code scan the file & put the the commmands line by line in an array 
    */
    while (fscanf(Main, "%[^\n]\n", line) != EOF)
    {
        reset();
        char commands[14] = {'\0'};
        /**
         * @code all the letters become capital
        */
        for (int j = 0; j < sizeof(line); j++)
        {
            line[j] = toupper(line[j]);
        }
        /**
         * @code we put the first word of each line in other array
        */
        for (k = 0; line[k] != ' ' && line[k] != '\n' && line[k] != '/' && line[k] != '\0'; k++)
        {
            commands[k] = line[k];
            // if (line[k + 1] == '\0')
            // {
            //     line[k + 1] = ' ';
            // }
        }
        // commands[k] = '\0';
        if (strcmp(commands, "EXIT") == 0)
        {
            break;
        }
        else if (strcmp(commands, "ADD") == 0)
        {
            sscanf(line, "ADD S%d, S%d, S%d", &result, &value, &value1);
            flag = IndexError(result, value, value1, commands);
            if (flag == 1)
            {
                ADD(result, value, value1);
            }
        }
        else if (strcmp(commands, "SUB") == 0)
        {
            sscanf(line, "SUB S%d, S%d, S%d", &result, &value, &value1);
            flag = IndexError(result, value, value1, commands);
            if (flag == 1)
            {
                SUB(result, value, value1);
            }
        }
        else if (strcmp(commands, "AND") == 0)
        {
            sscanf(line, "AND S%d, S%d, S%d", &result, &value, &value1);
            flag = IndexError(result, value, value1, commands);
            if (flag == 1)
            {
                AND(result, value, value1);
            }
        }
        else if (strcmp(commands, "XOR") == 0)
        {
            sscanf(line, "XOR S%d, S%d, S%d", &result, &value, &value1);
            flag = IndexError(result, value, value1, commands);
            if (flag == 1)
            {
                XOR(result, value, value1);
            }
        }
        else if (strcmp(commands, "OR") == 0)
        {
            sscanf(line, "OR S%d, S%d, S%d", &result, &value, &value1);
            flag = IndexError(result, value, value1, commands);
            if (flag == 1)
            {
                OR(result, value, value1);
            }
        }
        else if (strcmp(commands, "ADDI") == 0)
        {
            sscanf(line, "ADDI S%d, S%d, %d", &result, &value, &value1);
            flag = IndexError(result, value, 1, commands);
            if (flag == 1)
            {
                ADDI(result, value, value1);
            }
        }
        else if (strcmp(commands, "SUBI") == 0)
        {
            sscanf(line, "SUBI S%d, S%d, %d", &result, &value, &value1);
            flag = IndexError(result, value, 1, commands);
            if (flag == 1)
            {
                SUBI(result, value, value1);
            }
        }
        else if (strcmp(commands, "ANDI") == 0)
        {
            sscanf(line, "ANDI S%d, S%d, %d", &result, &value, &value1);
            flag = IndexError(result, value, 1, commands);
            if (flag == 1)
            {
                ANDI(result, value, value1);
            }
        }
        else if (strcmp(commands, "XORI") == 0)
        {
            sscanf(line, "XORI S%d, S%d, %d", &result, &value, &value1);
            flag = IndexError(result, value, 1, commands);
            if (flag == 1)
            {
                XORI(result, value, value1);
            }
        }
        else if (strcmp(commands, "ORI") == 0)
        {
            sscanf(line, "ORI S%d, S%d, %d", &result, &value, &value1);
            flag = IndexError(result, value, 1, commands);
            if (flag == 1)
            {
                ORI(result, value, value1);
            }
        }
        else if (strcmp(commands, "MOV") == 0)
        {
            if (line[8] == 'S' || line[9] == 'S')
            {
                sscanf(line, "MOV S%d, S%d", &result, &value);
                flag = IndexError(result, value, 1, commands);
                if (flag == 1)
                {
                    MOV(result, S[value]);
                }
            }
            else
            {
                sscanf(line, "MOV S%d, %d", &result, &value);
                flag = IndexError(result, 1, 1, commands);
                if (flag == 1)
                {
                    MOV(result, value);
                }
            }
        }
        else if (strcmp(commands, "SWP") == 0)
        {
            sscanf(line, "SWP S%d, S%d", &value, &value1);
            flag = IndexError(value, value1, 1, commands);
            if (flag == 1)
            {
                SWP(value, value1);
            }
        }
        else if (strcmp(commands, "DUMP_REGS") == 0)
        {
            DUMP_REGS();
        }
        else if (strcmp(commands, "DUMP_REGS_F") == 0)
        {
            DUMP_REGS_F();
        }
        else if (strcmp(commands, "INPUT") == 0)
        {
            INPUT();
        }
        else if (strcmp(commands, "OUTPUT") == 0)
        {
            OUTPUT();
        }
        else if (strcmp(commands, "JMP") == 0)
        {
            countjmp++;
            if (countjmp > 5) 
            {
                red();
                printf("\nERROR in JMP! infinite loop!\n");
                reset();
                // fscanf(Main, "%[^\n]\n", line);
                // countjmp = 0;
            }
            else
            {
                int charscount = 0, linecount = 1;
                sscanf(line, "JMP %d", &value);
                if (value <= 0)
                {
                    red();
                    printf("\nError in JMP! Negative Line JMP!\n");
                    reset();
                }
                else if (value > linecheck)
                {
                    red();
                    printf("\nError in JMP! JMP to the line that doesn't exist!\n");
                    reset();
                }
                else
                {
                    rewind(Main);
                    while (linecount != value)
                    {
                        charscount++;
                        if (fgetc(Main) == '\n')
                        {
                            linecount++;
                        }
                    }
                    fseek(Main, charscount + 1, SEEK_SET);
                    fscanf(Main, "%[^\n]\n", line);
                    // for (k = 0; line[k] != ' '; k++)
                    // {
                    //     commands[k] = line[k];
                    // }
                    // commands[k] = '\0';
                }
            }
        }
        else if (strcmp(commands, "SKIE") == 0)
        {
            sscanf(line, "SKIE S%d, S%d", &value, &value1);
            flag = IndexError(value, value1, 1, commands);
            if (flag == 1)
            {
                if (S[value] == S[value1])
                {
                    fscanf(Main, "%[^\n]\n", line);
                    // for (k = 0; line[k] != ' '; k++)
                    // {
                    //     commands[k] = line[k];
                    // }
                    // commands[k] = '\0';
                }
            }
        }
        else if (strcmp(commands, "MULL") == 0)
        {
            sscanf(line, "MULL S%d, S%d", &value, &value1);
            flag = IndexError(value, value1, 1, commands);
            if (flag == 1)
            {
                MULL(value, value1);
            }
        }
        else if (strcmp(commands, "DIV") == 0)
        {
            sscanf(line, "DIV S%d, S%d", &value, &value1);
            flag = IndexError(value, value1, 1, commands);
            if (flag == 1)
            {
                DIV(value, value1);
            }
        }
        else if (strcmp(commands, "PUSH") == 0)
        {
            sscanf(line, "PUSH S%d", &value);
            flag = IndexError(value, 1, 1, commands);
            if (flag == 1)
            {
                PUSH(value);
            }
        }
        else if (strcmp(commands, "POP") == 0)
        {
            sscanf(line, "POP S%d", &value);
            flag = IndexError(value, 1, 1, commands);
            if (flag == 1)
            {
                POP(value);
            }
        }
        else
        {
            red();
            printf("\nERROR! \n The Input is wrong! Please try again. \n");
            reset();
        }
    }
    fclose(Main);

    return 0;
}