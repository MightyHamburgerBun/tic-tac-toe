te
#include <iostream>
//получение элемента по координатам
char element(std::string field, int x, int y)
{
    return field[x * 3 + y];
}
//получение колонки по индексу
std::string col(std::string field, int y)
{
    std::string col = "   ";
    for (int i = 0; i < 3; i++)
    {
        col[i] = element(field, i, y);
    }
    return col;
}
//получение диагонали
std::string diagonal(std::string field, int p)
{
    std::string diagonal = "   ";
    if (p == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            diagonal[i] = element(field, i, i);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            diagonal[i] = element(field, i, 2 - i);
        }
    }
    return diagonal;
}
//получение количества X/O
int count(std::string field, char c)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (field[i] == c) count++;
    }
    return count;
}
//проверка на недопустимые символы и их количество
bool incorrect(std::string field)
{
    if (field.length() != 9) return true;
    std::string valid = "XO.";
    for (int i = 0; i < 9; i++)
    {
        if (valid.find(field[i]) == std::string::npos) return true;
    }
    if (count(field,'X') != count(field,'O') && count(field,'X') != count(field,'O') + 1) return true;
    return false;
}
// Incorrect; Petya won(X); Vanya won(O); Nobody
std::string analysis(std::string firstRow, std::string secondRow, std::string thirdRow)
{
    std::string field = firstRow + secondRow + thirdRow;
    if (incorrect(field)) return "Incorrect\n";
    //считаем победные ряды
    int xWon = 0, oWon = 0;
    if (firstRow == "XXX") xWon++;
    else if (firstRow == "OOO") oWon++;
    if (secondRow == "XXX") xWon++;
    else if (secondRow == "OOO") oWon++;
    if (thirdRow == "XXX") xWon++;
    else if (thirdRow == "OOO") oWon++;
    //считаем победные колонки
    for (int i = 0; i < 3; i++)
    {
        if (col(field,i) == "XXX") xWon++;
        else if (col(field,i) == "OOO") oWon++;
    }
    //проверяем диагонали
    if (diagonal(field,0) == "XXX") xWon++;
    else if (diagonal(field,0) == "OOO") oWon++;
    if (diagonal(field,1) == "XXX") xWon++;
    else if (diagonal(field,1) == "OOO") oWon++;

    if (oWon + xWon == 0) return "Nobody\n";
    if (oWon == 1)
    {
        if (count(field,'X') == count(field,'O')) return "Vanya won\n";
        else return "Incorrect\n";
    }
    else
    {
        if (count(field,'X') == count(field,'O') + 1) return "Petya won\n";
        else return "Incorrect\n";
    }
}

int main() {
    std::string firstRow, secondRow, thirdRow;
    std::cout << "Input:\n";
    std::cin >> firstRow;
    std::cin >> secondRow;
    std::cin >> thirdRow;
    std::cout << analysis(firstRow, secondRow, thirdRow);
}