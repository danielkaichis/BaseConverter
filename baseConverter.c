/*
 * File: bihex.c
 * Author: Daniel Kaichis
 * Purpose: To take a users inputted string in a base of either binary, hexadecimal,
 *          or decimal and convert it to a base of their choosing (binary, 
 *          hexadecimal, or decimal). The program will validate the users input
 *          to check if they have entered a string in one of the accepted bases
 *          and identify the base they have entered before converting to the
 *          base of their choosing.
 * Status: DONE
 * Created on February 18, 2020, 12:31 PM
 */

#include <stdio.h>
#include <stdlib.h>

// Purpose: a function that returns the answer of a power
// Parameters: base - the base of the power
//             exponent - the exponent of the power
// Returns: the value of (base ^ exponent)
int power( int base, int exponent ) {
   int answer = 1;
   int index;
   for ( index = 0; index < exponent; index++ ) {
       answer *= base;  // same as answer = answer * base
   }
   return answer;
}

int main(int argc, char** argv) {
    
    // initiate variables
    // max size of the arrays
    int ARRAY_SIZE = 32;
    char bihex[ARRAY_SIZE + 1];
    char decBiConvert[ARRAY_SIZE + 1];
    char decHexConvert[ARRAY_SIZE + 1];
    int stringlength = 0;
    int bihexpos = 0;
    char inputBase = 'x';
    char* inputBaseText = "default";
    // initialize variables to store the base (base 2, base 10, base 16) of the users input
    // Assume string is binary until the base of the string is checked and found
    int isBinary = 1;
    int isDec = 0;
    int isHex = 0;
    // set runconverter to 1. When this value is set to 0 because the user enters
    // a value of 0 then the program will quit.
    int runConverter = 1;
    // set default value of the base to convert to
    char convertBase = 'x';
    char* convertBaseText = "default";
    // base exponent in which the binary value is put to the power of
    int binaryExponent = 0;
    // intermediate integer in base 10 (decimal) that the users inputed string is
    // converted to before it is converted to the base that the user wants to be outputted
    int intermediate = 0;
    int remainder = 0;
    int quotient = 0;
    int asciiToDec = 0;

    // welcome message
    printf("Welcome to the base converter!\n");

    // loop bihex converter when the value 0 is entered
    while (runConverter) {
        // set bihexpos to 0 at the beginning of the program to start at the beginning
        // of the new string entered
        bihexpos = 0;
        // set isBinary to 1 at the beginning of the program. This value will remain
        // one until the program checks what base the entered value is.
        isBinary = 1;
        // set isHex to 0 at the beginning of the program.
        isHex = 0;
        // set isDec to 0 at the beginning of the program.
        isDec = 0;
        // Terminate each array by setting the first value to null (0 in ascii)
        bihex[0] = 0;
        decBiConvert[0] = 0;
        decHexConvert[0] = 0;
            
        // Get user to input string
        printf("Please enter a value in the form of binary, hexadecimal, or decimal to convert [0 to quit]: ");
        scanf("%[^\n]s", bihex);
        fgetc(stdin);
        printf("You entered the value: '%s'\n", bihex);
        
        // iterate through the inputed string
        while ((bihex[bihexpos] != 0) && (bihexpos < ARRAY_SIZE + 1)) {
            // check if value at each index is not between 0-9, is not between
            // a-f, and is not between A-F, which are the ranges that make
            // the string valid. As soon as a value in the string does not
            // meet the if condition, the string is invalid and a message
            //is printed asking the user to try again
            if  ( ((bihex[bihexpos] < 48) || (bihex[bihexpos] > 57)) && ((bihex[bihexpos] < 65) || (bihex[bihexpos] > 70)) && ((bihex[bihexpos] < 97) || (bihex[bihexpos] > 102)) ) {
                // the first value is '0' and second value is 'x' or 'X' and the program has
                // not determined that the input was hexadecimal already.
                if ((bihex[0] == 48) && ((bihex[1] == 120) || (bihex[1] == 88)) && (isHex == 0)) {
                    // '0x' was entered as the first two values in the string and the other characters are valid
                    // which means that the user entered a hexadecimal string.
                    isHex = 1;
                    // move position to index 2 which is the first index after the
                    // 0x to validate the rest of the users input
                    bihexpos = 2;
                    // users input is between 0-9 (inclusive), between a-f or between A-F
                    if ( ((bihex[bihexpos] >= 48) && (bihex[bihexpos] <= 57)) || ((bihex[bihexpos] >= 65) && (bihex[bihexpos] <= 70)) || ((bihex[bihexpos] >= 97) && (bihex[bihexpos] <= 102)) ) {
                        // increment index/position and go back to start of loop to
                        // continue validating the users input character by character
                        bihexpos++;
                        continue;
                    // user entered an invalid character
                    } else {
                        // user did not enter any characters after the 0x. This
                        // means they would like to quit as this evaluates to 0.
                        if (bihex[bihexpos] == 0) {
                            // set run converter to 0 and break the loop to quit
                            // the program once the intermediate is evaluated to see
                            // if it is 0.
                            runConverter = 0;
                            break;
                        }
                        // user entered invalid character
                        // print invalid message and ask user to enter new value.
                        // scan new value into the array.
                        printf("Your input of %s is invalid. Please enter a new value: ", bihex);
                        scanf("%[^\n]s", bihex);
                        fgetc(stdin);
                        // reset position to 0 and because the user entered a invalid
                        // string, set isHex to 0 as well because they now entered
                        // an entirely new string. 
                        bihexpos = 0;
                        isHex = 0;
                        // go back to the beginning of the loop and validate new string
                        continue;
                    }
                } 
                // user entered a character in their string that is invalid. 
                // prompt user to input new string
                printf("Your input of %s is invalid. Please enter a new value: ", bihex);
                scanf("%[^\n]s", bihex);
                fgetc(stdin);
                // reset back to the beginning of the array if the user inputted
                // a invalid value
                bihexpos = 0;
                // user entered new string so reset isHex to 0;
                isHex = 0;
            // user input at bihexpos index is valid so continue to increment 
            // through the array.
            } else {
                // if the value in the string at index bihexpos is valid, increment
                // bihexpos by 1 and check the next value in the string.
                bihexpos++;
            }
        // end of input validation loop
        }
        // set stringlength to the length of the array as the position after looping
        // through the users inputed value to validate will be the last value in the array that is
        // not null.
        stringlength = bihexpos;
        // reset bihexpos to 0 to reiterate through the inputed value and figure
        // out which base the inputed value is in the following loop.
        bihexpos = 0;
        // iterate through the string until a null value or the end of the string is reached.
        // this loop will only run once the user inputs a valid string in
        // the form of base 2, base 10, or base 16.
        while ((bihex[bihexpos] != 0) && (bihexpos < stringlength)) {
            // If the value at index bihexpos is not 0 or 1 then it is not binary
            // and the program checks if it is hex or decimal
            if ((bihex[bihexpos] != 48) && (bihex[bihexpos] != 49)) {
                // If the value at index bihexpos is between 0-9 then the
                // string is a decimal string (base 10)
                if ( ((bihex[bihexpos] >= 48) && (bihex[bihexpos] <= 57)) ) {
                    // If the user inputed 0x to start the string, the string
                    // cannot be a decimal string and must be a hex string.
                    if (isHex) {
                        isHex = 1;
                        isDec = 0;
                    } else {
                        // the value at index bihexpos was decimal. this value will
                        // only change if a later value in the string is a
                        // hexadecimal value
                        isDec = 1;
                    }
                    // the string is not binary
                    isBinary = 0;
                    // Increment bihexpos by 1 and continue to iterate through
                    // the users string to check if there are any hexadecimal
                    // values in the string that would make the string a
                    //hexadecimal string.
                    bihexpos++;
                // If any value does not meet the condition of being
                // between 0-9 then it is a hexadecimal string because
                // it is valid and contains at least one letter from a-f
                // or A-F.
                } else {
                    // string is hexadecimal
                    isHex = 1;
                    // string is not binary
                    isBinary = 0;
                    // string is not decimal
                    isDec = 0;
                    // there is no need to continue to iterate through the string because
                    // the string contains a letter from a-f or A-F which are
                    // characters that can only be found in a hexadecimal string
                    // and not a binary or decimal string.
                    break;
                }
            // The value at index bihexpos was 1 or 0
            } else {
                // Increment bihexpos by 1 and continue to iterate through
                // the users string to check if there are any decimal or hexadecimal
                // values in the string that would make the string a
                // decimal or hexadecimal string. If the entire string goes through
                // the loop and the only characters are 0 or 1 so the default value
                // of isBinary remains 1 as declared at the beginning of the program.
                bihexpos++;
            }
        // end of loop to determine base of input
        }

        // the string is binary so assign the variable to print the base of the
        // users string to "binary"
        if (isBinary) {
            inputBase = 'b';
            inputBaseText = "binary";
        // the string is decimal so assign the variable to print the base of the
        // users string to "decimal"
        } else if (isDec) {
            inputBase = 'd';
            inputBaseText = "decimal";
        // the string is hexadecimal so assign the variable to print the base of the
        // users string to "hexadecimal"
        } else {
            inputBase = 'h';
            inputBaseText = "hexadecimal";
        }

        // ask user to input to what base they would like to convert their string to
        printf("To what base would you like to convert the %s value %s?\n", inputBaseText, bihex);
        printf("Press b to convert to binary, d to convert to decimal,\n");
        printf("or h to convert to hexadecimal [b,d,h]: ");
        scanf("%c", &convertBase);
        fgetc(stdin);
        // keep asking the user to input a valid base of 'b', 'd', or 'h' (binary,
        // decimal, hexadecimal) to convert to until they input a valid base
        while ((convertBase != 98) && (convertBase != 100) && (convertBase != 104)) {
            printf("Your input of %c is invalid. Please enter a valid base.\n", convertBase);
            printf("Press b to convert to binary, d to convert to decimal,\n");
            printf("or h to convert to hexadecimal [b,d,h]: ");
            scanf("%c", &convertBase);
            fgetc(stdin);
        }

        // the user wants to convert to binary so set convert base text to "binary"
        if (convertBase == 'b') {
            convertBaseText = "binary";
        // the user wants to convert to decimal so set convert base text to "decimal"
        } else if (convertBase == 'd') {
            convertBaseText = "decimal";
        // the user wants to convert to hexadecimal so set convert base text to "hexadecimal"
        } else if (convertBase == 'h') {
            convertBaseText = "hexadecimal";
        }
        // print the base the program will convert the users input into
        printf("You are converting to %s.\n", convertBaseText);

        // set bihexpos to 0 to iterate through the inputed value for the
        // conversions below.
        bihexpos = 0;
        // set intermediate to 0 so that when the user runs the program multiple
        // times without quitting the value is reset and recalculated.
        intermediate = 0;
        // set the value of the binary exponent to 0 which will be incremented
        // as the value is converted from binary to decimal
        binaryExponent = 0;
        // user entered a binary value
        if (isBinary) {
            // iterate through the binary value to convert to decimal
            while ((bihex[bihexpos] != 0) && (bihexpos < stringlength)) {
                /* The ascii value of 1 is 49 and the ascii value of 0 is 48 so
                by starting at the last index of the array and taking the ascii
                value minus 48, each value is converted to its binary value to
                use the binary to decimal conversion. If the value is 0 then
                when it is multiplied by 2 to the power of the binary exponent
                it will be 0 so there will be no change in the intermediate value
                however if the binary number is 1 at the index the loop is at
                then it will be multiplied by 2 to the power of the exponent
                which is incremented as the program iterates through the string.
                Because the algorithm for binary to decimal is to multiply each
                binary value by the 2 to the power of an exponent that has a
                starting value of 0 at the last index of a binary number
                (i.e starting at the last 1 in 1011), the program starts at
                the last index of the array in which the binary value is stored
                (stringlength - bihexpos - 1) and iterates forward (as bihexpos
                increases by 1, that index will decrease by one, iterating
                from the last index of the array to the first index). */
                intermediate += (bihex[stringlength - bihexpos - 1] - 48) * power(2, binaryExponent);
                // increment binary exponent by 1 to move to the next power of 2
                // to follow the algorithm described above
                binaryExponent++;
                // increment bihexpos by 1
                bihexpos++;
            }
        // user entered a decimal value
        } else if (isDec) {
            // iterate through the inputed value to convert the decimal
            // value of the string array to an integer.
            while ((bihex[bihexpos] != 0) && (bihexpos < ARRAY_SIZE + 1)) {
                /* Subtracting 48 from the ascii value of each decimal value
                will convert the ascii value to decimal value to be multiplied
                by 10 to the power of the bihexpos which will convert each the
                decimal stored in the string array to a decimal. This algorithm
                starts with the last index of the array and iterates forward to
                each "decimal place" until it gets through the first index of
                the array. Eg. 321 is converted as follows 1 * 10^0 + 2 * 10^1
                + 3 * 10^2. This block of code essentially takes each decimal place
                (ones, tens, hundreds, etc.) and multiplies the values in each 
                position by 10 and adds them together to convert the decimal 
                value stored in an array to an integer. */
                intermediate += (bihex[stringlength - bihexpos - 1] - 48) * power(10, bihexpos);
                // increment bihexpos by 1 and continue to loop through the array
                bihexpos++;
            }
        // user entered a hexadecimal value
        } else {
            // iterate through the inputted value stored as an array
            while ( (bihex[bihexpos] != 0) && (bihexpos < stringlength) && (bihex[stringlength - bihexpos - 1] != 120)) {
                // Users inputted value at the last index in the array is between 
                // 65-70 in ascii (A-F) so asciiToDec is 55 because 55 is the 
                // number to subtract from each ascii value to convert it to decimal
                // I.e 'A' is 65 in ascii and 10 in decimal. 65 - 55 = 10. 
                if (((bihex[stringlength - bihexpos - 1] >= 65) && (bihex[stringlength - bihexpos - 1] <= 70))) {
                    asciiToDec = 55;
                // Users inputted value at the last index in the array is between 
                // 97-102 in ascii (A-F) so asciiToDec is 87 because 87 is the 
                // number to subtract from each ascii value to convert it to its decimal form
                // I.e 'a' is 97 in ascii and 10 in decimal. 97 - 87 = 10. 
                } else if (((bihex[stringlength - bihexpos - 1] >= 97) && (bihex[stringlength - bihexpos - 1] <= 102))) {
                    asciiToDec = 87;
                // Users inputted value at the last index in the array is between 
                // 48-57 in ascii (A-F) so asciiToDec is 48 because 48 is the 
                // number to subtract from each ascii value to convert it to its decimal form
                // I.e '7' is 55 in ascii and 7 in decimal. 55 - 48 = 7.     
                } else {
                    asciiToDec = 48;
                }
                // to convert from hexadecimal to decimal, we must convert from
                // right to left in a number so string length - position - 1 will
                // start at the last character of the user input stored as an array,
                // and as position is incremented the program will read through 
                // the array from right to left. In this algorithm, each value is
                // converted to its integer form by subtracting the asciiToDec converter
                // variable, and then multiplied by 16 to the power of whatever
                // position in the array the counter is on. The intermediate value
                // is incremented by this value every time the next index is evaluated
                // until the loop reaches a null value and exits with the intermediate
                // being the hexadecimal value converted to decimal
                intermediate += ((bihex[stringlength - bihexpos - 1]) - asciiToDec) * power(16, bihexpos);
                // increment position counter
                bihexpos++;
            }
        }
        // if the intermediate evaluates to 0, quit the program
        if ((intermediate == 0) || (runConverter == 0)) {
            // closing message
            printf("Your inputted value was 0 so the program is quitting.\n");
            printf("Thank you for using this bihex converter!\n");
            break;
        }

        // if user inputed a hexadecimal value and they would like to convert
        // to a hexadecimal value, print out their input so the hexadecimal value
        // can be outputted with the same case (capital or lower case) that they inputted.
        if ((inputBase == 104) && (convertBase == 104)) {
            printf("Your hexadecimal value in hexadecimal is %s.\n", bihex);
            // go back to the start of the loop and use the converter again
            continue;
        // user inputed a binary value and wants to have a binary value outputted
        // so print their input to eliminate the need of conversion.
        } else if ((inputBase == 98) && (convertBase == 98)) {
            printf("Your binary value in binary is %s.\n", bihex);
            // go back to the start of the loop and use the converter again
            continue;
        // user inputed a decimal value and wants to have a decimal value outputted
        // so print their input to eliminate the need of conversion.
        } else if ((inputBase == 100) && (convertBase == 100)) {
            printf("Your decimal value in decimal is %s.\n", bihex);
            // go back to the start of the loop and use the converter again
            continue;
        }
        // reset bihex position to 0 to convert from decimal to binary
        bihexpos = 0;
        // user wants to convert to binary
        if (convertBase == 98) {
            // because we are checking the remainder by dividing by 2 every time, the value will
            // eventually reach a decimal with 0 as the digit in the ones place so
            // the loop will exit because intermediate is a decimal and the decimal
            // value will be 0.
            while (intermediate > 0) {
                // if the decimal value of the users input divided by 2 has a 
                // remainder of 1, then the binary value is 1.
                if (intermediate % 2 == 1) {
                    // set the value at the index of the array to 1
                    decBiConvert[bihexpos] = 49;
                    // divide intermediate by 2 to reflect the change to the value
                    // after checking the remainder
                    intermediate = intermediate / 2;
                // if the decimal value of the users input divided by 2 has a 
                // remainder of 0, then the binary value is 0 because when any
                // number is divided by 2 it will have a remainder of 1 or 0.
                } else {
                    // set the value at the index of the array to 0
                    decBiConvert[bihexpos] = 48;
                    // divide intermediate by 2 to reflect the change to the value
                    // after checking the remainder
                    intermediate = intermediate / 2;
                }
                // increment index/position in the array by 1
                bihexpos++;
            }
            // print users value in binary
            printf("Your value in binary is: ");
            // When you convert to binary the results come back in backwards order
            // so this loop prints the array character by character backwards to
            // put the binary string in the correct order
            while (bihexpos > 0) {
                // start at last index because to convert the position ended at the
                // last index of the array.
                printf("%c", decBiConvert[bihexpos - 1]);
                // subtract one from the position counter to work backwards in the array
                bihexpos--;
            }
            printf("\n");
            
        // user wants to convert to hexadecimal
        } else if (convertBase == 104) {
            // because we dividing by 16 every time, the value will
            // eventually reach a decimal with 0 as the digit in the ones place so
            // the loop will exit because intermediate is a decimal and the decimal
            // value will be 0.
            while  (intermediate > 0)  {
                // divide the intermediate by 16 to get the quotient. All values 
                // are integers so only the integer value is stored and the decimal
                // places are forgotten. 
                quotient = intermediate / 16;
                // the remainder is equal to the intermediate minus the quotient
                // times 16. The remainder is the hexadecimal value that has been
                // converted from decimal. Multiplying the quotient with 16 will
                // give a value that does not include the decimal places that were 
                // lost so the difference between the intermediate and that value
                // is the remainder which is a hexadecimal value.
                remainder = intermediate - (quotient * 16);
                // the remainder is greater than 10 so it must be converted to a
                // letter form in ASCII
                if (remainder >= 10) {
                    // add 55 to convert the remainder in integer form to a letter
                    // in ASCII because the array stores ASCII values and not integer
                    // values because the hexadecimal number system does not only
                    // include integers
                    decHexConvert[bihexpos] = remainder + 55;
                } else {
                    // add 48 to convert the remainder in integer form to a number
                    // from 0-9 in ASCII to be stored in the array.
                    decHexConvert[bihexpos] = remainder + 48;
                }
                // divide intermediate by 16 once the remainder is stored to continue
                // finding the remainder of the remainder etc, to convert the decimal
                // value to a hex value.
                intermediate /= 16;
                // increment bihexpos by 1 to continue incrementing indexes in the
                // conversion array so the remainders can be stored.
                bihexpos++;
            }
            // Print the users inputted value in hexadecimal
            printf("Your hexadecimal value is: 0x");
            // When you convert to hexadecimal the results come back in backwards order
            // so this loop prints the array character by character backwards to
            // put the hexadecimal string in the correct order
            while ((bihexpos > 0)) {
                // start at last index because to convert the position ended at the
                // last index of the array.
                printf("%c", decHexConvert[bihexpos-1]);
                bihexpos--;
            }
            printf("\n");
        } else {
            // print the users value converted to decimal. No conversion is 
            // required because the intermediate value for converting from base 
            // to base is a decimal value.
            printf("Your value in decimal is %d\n", intermediate);
        }
    }
    
    return (EXIT_SUCCESS);
}