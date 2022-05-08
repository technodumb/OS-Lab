#! /bin/bash

# write a bash script for a menu driven calculator
# the script should have the following options:
# 1. add
# 2. subtract
# 3. multiply
# 4. divide
# 5. power
# 6. quit
# numbers should be inputted for each operation
# the script should output the result of each operation
# the script should exit when the user enters 6
ch="y"
while [ $ch == "y" ] 
do
    read -p "Enter the first number: " num1
    read -p "Enter the second number: " num2
    
    echo "           Menu"
    echo "1. Add"
    echo "2. Subtract"
    echo "3. Multiply"
    echo "4. Divide"
    echo "5. Power"
    read -p "Enter your choice: " choice
    case $choice in
        1)  echo "The sum of $num1 and $num2 is: $((num1 + num2))"
            ;;
        2)  echo "The difference between $num1 and $num2 is: $((num1 - num2))"
            ;;
        3)  echo "The product of $num1 and $num2 is: $((num1 * num2))"
            ;;
        4)  if [ $num2 == 0 ]
            then
                echo "Division by zero is not possible"
            else 
                echo "The result of $num1/$num2 is: $((num1 / num2))"
            fi
            ;;
        5)  result=1
            for((i=1;i<=num2;i++))
            do
                result=$((result * num1));
            done
            echo "The result of $num1^$num2 is: $result";
            ;;
        *)  echo "Invalid choice";
            ;;
    esac
    echo ""
    read -p "Would you like to continue (y/n) :" ch
done
