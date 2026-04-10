#!/bin/bash
 
while true
do
  echo "1.Area of circle"
  echo "2.Circumference of  circle"
  echo "3.Area of rectangle"
  echo "4.Area of square"
  echo "5.Exit"

  read choice

  case $choice in
  1)
    echo "Enter radius:"
    read r
    area=$(echo "3.14*$r*$r"|bc)
    echo "Area=$area"
    ;;

  2)
    echo "Enter radius:"
    read r
    circumference=$(echo "2*3.14*$r"|bc)
    echo "Circumference=$circumference"
    ;;

  3)
    echo "Enter length:"
    read l
    echo "Enter breadth:"
    read b
    area=$(echo "2*$l*$b"|bc)
    echo "Area of rectangle=$area"
    ;;

  4)
    echo "Enter side:"
    read s
    area=$(echo "$s*$s"|bc)
    echo "Area of square=$area"
    ;;

  5)
    exit
    ;;
  *)
    echo "Invalid choice"
    ;;
  esac
done
