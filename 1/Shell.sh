#!/bin/bash

#Function for creating a phone record
createAddressBook(){
    touch addressbook.txt
    echo "Book Created !!!"
    echo ""
}

addRecord(){
    echo -e -n "what is the name ? "
    read name
    echo -e -n "address : "
    read address
    echo -e -n "what is the number ? "
    read mob
    echo -e " $name | \t | $address | \t | $mob | \t |" >> addressbook.txt
    echo "Record added!!!"
    echo ""
}

deleteRecord(){
    echo -n -e "What is the line you want to delete :\t"
    read line
    sed -i $line"d" addressbook.txt
    echo "Record deleted !!!"
    echo ""
}

updateRecord(){
    echo -n -e "Line for which you want to update : "
    read line
    echo -e -n "what is the name ? "
    read name
    echo -e -n "address : "
    read address
    echo -e -n "what is the number ? "
    read mob
    sed -i $line"c$name | $address | $mob" addressbook.txt
    echo "Updated succcessfully!"
    echo ""
}

readAddressBook(){
    cat addressbook.txt
    echo ""
}

while true; do
    echo ""
    echo "MENU"
    echo "1.Create a address book "
    echo "2.View address book"
    echo "3.Insert a Record"
    echo "4.Delete Records"
    echo "5.Modify Records"
    echo "6.Exit"
    echo -n "Your choice : "
    read choice

    case $choice in 
        1)
            createAddressBook;;
        2) 
            echo "Reading address book"
            readAddressBook;;
        3)
            addRecord;;
        4)
            deleteRecord;;
        5) 
            updateRecord;;
        6) 
            break;;
        *)
            echo "invalid choice"

    esac
done
