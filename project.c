#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int S[32];
int conregs[8];
int stack[50];

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

void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}

void yellow()
{
    printf("\033[1;33m");
}

void blue()
{
    printf("\033[1;34m");
}

void purple()
{
    printf("\033[1;35m");
}

void reset()
{
    printf("\033[1;0m");
}

void ADD(int rd, int rs, int rt)
{
    S[rd] = S[rs] + S[rt];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
    overflowflag_ADD(S[rs], S[rt], S[rd]);
}

void SUB(int rd, int rs, int rt)
{
    S[rd] = S[rs] - S[rt];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
    overflowflag_SUB(S[rs], S[rt], S[rd]);
}

void AND(int rd, int rs, int rt)
{
    S[rd] = S[rt] & S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}

void XOR(int rd, int rs, int rt)
{
    S[rd] = S[rt] ^ S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}

void OR(int rd, int rs, int rt)
{
    S[rd] = S[rt] | S[rs];
    parityflag(S[rd]);
    zeroflag(S[rd]);
    signflag(S[rd]);
}

void ADDI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] + Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
    overflowflag_ADD(S[rs], Imm, S[rt]);
}

void SUBI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] - Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
    overflowflag_SUB(S[rs], Imm, S[rt]);
}

void ANDI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] & Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}

void XORI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] ^ Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}

void ORI(int rt, int rs, int Imm)
{
    S[rt] = S[rs] | Imm;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}

void MOV(int rt, int Imm)
{
    S[rt] = Imm;
}

void SWP(int rt, int rs)
{
    int t;
    t = S[rt];
    S[rt] = S[rs];
    S[rs] = t;
}

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

void INPUT()
{
    scanf("%d", &S[0]);
}

void OUTPUT()
{
    blue();
    printf("%d, ", S[0]);
    reset();
}

void DIV(int rs, int rt)
{
    int quot;
    quot = S[rt] / S[rs];
    S[rs] = S[rt] % S[rs];
    S[rt] = quot;
    parityflag(S[rt]);
    zeroflag(S[rt]);
    signflag(S[rt]);
}

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

void PUSH(int rs)
{
    for (int i = 0; i < 50; i++)
    {
        stack[i + 1] = stack[i];
    }
    stack[0] = S[rs];
}

void POP(int rt)
{
    S[rt] = stack[0];
    for (int i = 0; i < 50; i++)
    {
        stack[i] = stack[i + 1];
    }
}

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

int main(int argc, char *argv[])
{
    int flag, linecheck = 0, k;
    FILE *Main;
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
    while (fscanf(Main, "%[^\n]\n", line) != EOF)
    {
        linecheck++;
    }
    rewind(Main);
    while (fscanf(Main, "%[^\n]\n", line) != EOF)
    {
        reset();
        countjmp++;
        char commands[14] = {'\0'};
        for (int j = 0; j < sizeof(line); j++)
        {
            line[j] = toupper(line[j]);
        }
        for (k = 0; line[k] != ' '; k++)
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
            if (countjmp >= 5)
            {
                red();
                printf("\nERROR in JMP! infinite loop!\n");
                reset();
                fscanf(Main, "%[^\n]\n", line);
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