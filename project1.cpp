#include <iostream>
using namespace std;

bool isValidBase(char base){ // This function checks of a user input is valid or not.
    if(base == 'A' || base == 'C' || base == 'T' || base == 'G'){ // This if statement checks the input of the user to make sure it is A,C,T, or G.
        return true; // If the input is one of those characters, the function returns true.
    } 
    else{
        return false; // If the input is not one of those characters, the function returns false.
    }
}

bool isValidStrand(string strand){ // This function checks if the user has a valid string. 
    int length = strand.length(); // This variable is defined as the length of the user input.
    if(strand.empty()){ // This if statement checks if the string is empty and returns false if it is.
            return false;
    }
    for(int i = 0; i < length; i++){ // This loop checks each character of the string to make sure it is valid.
        if(strand[i] == 'A' || strand[i] == 'C' || strand[i] == 'T' || strand[i] == 'G'){ // This if statement checks if the character is A,C,T, or G.
            continue; // If it is one of those characters, the function continues the loop without running the rest of the loop.
        } 
        else{
            return false; // If the character is not one of those characters, the function will return false.
        }
    }
    return true; // After the loop has verified that all the characters in the string are valid, the function will return true.
}

double strandSimilarity(string strand1, string strand2){ // This function determines the similarity between two strings.
    int length1 = strand1.length(); // This defines a variable as the first string length.
    int length2 = strand2.length(); // This defines a variable as the second string length.
    double counter = 0; // This is the counter that will go up for every matching character.
    double similarity; // This is the similarity score that is the percentage of simliarity between two strings.

    if(length1 == length2){ // This if statement finds out if two strings are the same length.
        for(int i = 0; i < length1; i++){ // This loop runs for the entirety for a the inputted strings length.
            if(strand1[i] == strand2[i]){ // This if statement checks each corresponding character from string1 to string2 and determines if they are the same.
                counter++; // If the characters are the same, the counter goes up by one.
            }
        }
        similarity = counter/length1; // This variable is defined as the total matches divided by the length of the inputted strings.
        return similarity; // This is what is returned to the main function, the similarity score between the strings based on the counter and string length.
    } 
    else{ // If the string length does not match, this will run returning 0 to the main function.
        return 0; 
    }
}

int bestStrandMatch(string input_strand, string target_strand){ // This function determines the best matching string from an input and target strand.
    int inputLength = input_strand.length(); // This is the length of the input string.
    int targetLength = target_strand.length(); // This is the length of the target string.
    int end = inputLength - targetLength; // This is the difference in length between those strings.
    int counter2; // This variable is to find the right return value.
    double currentSimilarity; // This variable is to measure the current similarity of the substring of the input and the target string.
    double bestSimilarity = 0; // This variable is going to be defined as the best similarity between the two inputted strands.
    string subInput; // This will the substring that is measure against the target strand.

    if(inputLength > targetLength){ // If the input strand is longer than the target strand the code will find the best match between the two.
        for(int i = 0; i <= end; i++){ // This loop checks each substring against the target strand to find the best match.
            subInput = input_strand.substr(i, targetLength); // This defines the the subinput as a substring of the input.
            currentSimilarity = strandSimilarity(subInput, target_strand); // This will check the subInput against the target strand.

            if(currentSimilarity > bestSimilarity){ // If the similarity score from the the current substring with the input is larger than the best similarity, it will replace the best similarity with the current similarity.
                bestSimilarity = currentSimilarity;
                counter2=i; // This updates the counter to the position the substring starts from.
            }
        }
        cout << "Best similarity score: " << bestSimilarity << endl; // This finally ouputs the best similarity score from the previous if statement.
        return counter2; // This returns the proper position the substring starts at.
    }
    else if(inputLength == targetLength){ // If the lenghts of the input and target are the same, it just runs the previous function.
        bestSimilarity = strandSimilarity(input_strand, target_strand);
        cout << "Best similarity score: " << bestSimilarity << endl;
        return 0;
    }
    else{ // If the target is larger than the input string, this outputs that the similarity is 0.
        cout << "Best similarity score: 0.0" << endl;
        return -1; 
    }
}

void identifyMutations(string input_strand, string target_strand){ // This function finds mutations between two strings.

    int inputLength = input_strand.length();
    int targetLength = target_strand.length();
    int bestIndex;
    string subInput;

    if(inputLength > targetLength){ // This if statement compares the size of the strands, and runs the code accordingly.
        bestIndex = bestStrandMatch(input_strand, target_strand); // This runs the previous function to find the best match and alignment index.
        cout << "Best alignment index: " << bestIndex << endl;

        for(int i = 0; i < bestIndex; i++){ // This for loop finds all the deletions before the start of the target strand.
            cout << "Deletion at position " << i+1 << ": " << input_strand[i] << " is deleted in target strand" << endl;
        }

        for(int i = 0; i <= targetLength; i++){ // This for loop finds all the substituitions during the target strand.
            subInput = input_strand.substr(bestIndex, targetLength);
            if(subInput[i] != target_strand[i]){ // This if statement compares the characters of the input and target to see if they are the same or not. If they are not, the code finds the substituiton that has to be made on the input.
                cout << "Substitution at position " << i+bestIndex+1 << ": " << subInput[i] << " -> " << target_strand[i] << endl;
            }
        }

        for(int i = targetLength + bestIndex; i < inputLength; i++){ // This for loop finds all the deletes after the end of the target strand.
            cout << "Deletion at position " << i+1 << ": " << input_strand[i] << " is deleted in target strand" << endl;
        }

        return; // Ends the function.
    }
    else if(inputLength == targetLength){
        bestIndex = bestStrandMatch(input_strand, target_strand); // This runs the previous function to find the best match and alignment index.
        cout << "Best alignment index: " << bestIndex << endl;
        
        if(input_strand == target_strand){ // This compares the two strings to see if they are the exact same.
            cout << "No mutations found." << endl;
        }
        
        for(int i = 0; i <= inputLength; i++){ // This for loop finds all the substituitions during the target strand.
            if(input_strand[i] != target_strand[i]){ // This if statement compares the characters of the input and target to see if they are the same or not. If they are not, the code finds the substituiton that has to be made on the input.
                cout << "Substitution at position " << i+1 << ": " << input_strand[i] << " -> " << target_strand[i] << endl;
            }
        }
        return; // Ends the function.
    }
    else{
        bestIndex = bestStrandMatch(target_strand, input_strand); // This runs the previous function to find the best match and alignment index.
        cout << "Best alignment index: " << bestIndex << endl;

        for(int i = 0; i < bestIndex; i++){ // This for loop finds all the insertions before the start of the input strand.
            cout << "Insertion at position " << i+1 << ": " << target_strand[i] << " is inserted in target strand" << endl; 
        }

        for(int i = 0; i <= inputLength; i++){ // This for loop finds all the substituitions during the target strand.
            subInput = target_strand.substr(bestIndex, inputLength);
            if(subInput[i] != input_strand[i]){ // This if statement compares the characters of the input and target to see if they are the same or not. If they are not, the code finds the substituiton that has to be made on the input.
                cout << "Substitution at position " << i+bestIndex+1 << ": " << input_strand[i] << " -> " << subInput[i] << endl;
            }
        }

        for(int i = inputLength + bestIndex; i < targetLength; i++){ // This for loop finds all the insertions after the end of the input strand.
            cout << "Insertion at position " << i+1 << ": " << target_strand[i] << " is inserted in target strand" << endl;
        }
        return; // Ends the function.
    }
}

void transcribeDNAtoRNA(string strand){ // This function is for converting DNA into RNA.
    int strandLength = strand.length(); 

    for(int i = 0; i < strandLength; i++){ // This loop is to run through every character in the string and look for every instance of T and change it to U.
        if(strand[i] == 'T'){ // This if statement checks if the specific character in the string is T or not.
            strand[i] = 'U';
        }
    }
    cout << strand << endl; // Outputs the transcribed string at the end.
    return; // Ends the function.
}

void reverseComplement(string strand){ // This functions reverses the string and finds the inverse of the string.
    int strandLength = strand.length();
    string reverseString;

    for(int i = strandLength-1; i >= 0; i--){ // This loop runs from the end of the string to the beginning.
        if(strand[i] == 'A'){ // This checks if the specific character is A.
            reverseString += 'T'; // This adds T to the reverse string.
        }
        else if(strand[i] == 'T'){ // This checks if the specific character is T.
            reverseString += 'A'; // This adds A to the reverse string.
        }
        else if(strand[i] == 'C'){ // This checks if the specific character is C.
            reverseString += 'G'; // This adds G to the reverse string.
        }
        else{ // By process of elimination, the character must be G if it is not any of the other ones.
            reverseString += 'C'; // This adds C to the reverse string.
        }
    }

    cout << reverseString << endl; // Outputs the reverse complemented string at the end.
    return; // Ends the function.
}

void getCodingFrames(string strand){ // This function finds the codons in the given DNA strand.
    int strandLength = strand.length();
    int count2 = 0;

    for(int j = 0; j < strandLength; j++){ // This outer loop is to check for each instance of ATG.

        if(strand[j] != 'A' || strand[j+1] != 'T' || strand[j+2] != 'G'){ // This if statement is the the thing that checks for ATG.
            continue;
        }

        for(int i = j+3; i <= strandLength-1; i++){ // This inner for loop keeps checking for the end of the codon, and makes sure the codon is divisible by 3.
            if(strand[i] == 'T' && strand[i+1] == 'A' && strand[i+2] == 'A' && strand.substr(j, i+3-j).length() % 3 == 0){ // This if statment is the thing that checks for the end of the codon to be accurate.
                cout << strand.substr(j, i+3-j) << endl; // This outputs the proper codon.
                j = i+2; // This adds 2 onto j to start the outer loop after the end of the codon.
                count2++; // This is a counter that is checked after the for loops end to see if the for loops outputted something or not.
                break; // This breaks out of the inner loop to go back to the outer loop.
            } 
            else if(strand[i] == 'T' && strand[i+1] == 'A' && strand[i+2] == 'G' && strand.substr(j, i+3-j).length() % 3 == 0){ // This if statment is the thing that checks for the end of the codon to be accurate.
                cout << strand.substr(j, i+3-j) << endl; // This outputs the proper codon.
                j = i+2; // This adds 2 onto j to start the outer loop after the end of the codon.
                count2++; // This is a counter that is checked after the for loops end to see if the for loops outputted something or not.
                break; // This breaks out of the inner loop to go back to the outer loop.
            }
            else if(strand[i] == 'T' && strand[i+1] == 'G' && strand[i+2] == 'A' && strand.substr(j, i+3-j).length() % 3 == 0){ // This if statment is the thing that checks for the end of the codon to be accurate.
                cout << strand.substr(j, i+3-j) << endl;  // This outputs the proper codon.
                j = i+2; // This adds 2 onto j to start the outer loop after the end of the codon.
                count2++; // This is a counter that is checked after the for loops end to see if the for loops outputted something or not.
                break; // This breaks out of the inner loop to go back to the outer loop.
            }
        }
    }

    if (count2 == 0){ // This checks if the for loops outputted something.
        cout << "No reading frames found." << endl; // If they didn't output anything, this line of code will run.
        return; // This ends the function.
    }
    else{
        return; // This ends the function.
    }   
}

int main(){
    int input1 = 8;

    while(input1 < 0 || input1 > 7){ // This loop runs until a user exits the menu.
        cout << "--- DNA Analysis Menu ---" << endl;
        cout << "1. Calculate the similarity between two sequences of the same length" << endl;
        cout << "2. Calculate the best similarity between two sequences of either equal or unequal length" << endl;
        cout << "3. Identify mutations" << endl;
        cout << "4. Transcribe DNA to RNA" << endl;
        cout << "5. Find the reverse complement of a DNA sequence" << endl;
        cout << "6. Extract coding frames" << endl;
        cout << "7. Exit" << endl;
        cout << "Please enter your choice (1 - 7):" << endl; 
        cin >> input1;

        if(input1 < 0 || input1 > 7){ // This restarts the loop if the user enters an invalid menu number.
            cout << "Invalid input. Please select a valid option." << endl;
            continue;
        }

        if(input1 == 1){ // This runs if the user wnats to calulate similarity between two sequences of the same length.
            string sequence1;
            string sequence2;
            double similarity;
            bool validity = false;
            bool validity2 = false;

            while(validity == false){ // This runs until the user inputs a valid first sequence.
                cout << "Enter the first DNA sequence:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            while(validity2 == false){ // This runs until the user inputs a valid second sequence.
                cout << "Enter the second DNA sequence:" << endl;
                cin >> sequence2;
                validity2 = isValidStrand(sequence2); // This function checks the validity of the user inputted sequence.

                if(validity2 == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            if (sequence1.length() != sequence2.length()){ // This resets the user back the main menu if the sequences are not of the same length.
                cout << "Error: Input strands must be of the same length." << endl;
                input1 = 8;
                continue;
            }

            similarity = strandSimilarity(sequence1, sequence2); // This calls the strandSimilarity function to find the similarity score between the user inputted sequences.
            cout << "Similarity score: " << similarity << endl;
            input1 = 8; // This is so the loop can run again.
            continue; // This goes back to the loop after the funciton output.
        }
        else if(input1 == 2){ // THis runs if the user wants to calculate the best similarity between two strands of equal or non-equal length.
            string sequence1;
            string sequence2;
            bool validity = false;
            bool validity2 = false;

            while(validity == false){ // This runs until the user inputs a valid first sequence.
                cout << "Enter the first DNA sequence:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            while(validity2 == false){ // This runs until the user inputs a valid second sequence.
                cout << "Enter the second DNA sequence:" << endl;
                cin >> sequence2;
                validity2 = isValidStrand(sequence2); // This function checks the validity of the user inputted sequence.

                if(validity2 == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }


            if(sequence1 >= sequence2){ // This checks which sequence is bigger and decides the proper order to put the sequences in the bestStrandMatch function.
                bestStrandMatch(sequence1 , sequence2); // This runs the function based on the sequences inputted.
                input1 = 8; // This is so the loop can run again.
                continue; // This goes back to the loop after the funciton output.
            }
            else if(sequence1 < sequence2){ // This checks which sequence is bigger and decides the proper order to put the sequences in the bestStrandMatch function
                bestStrandMatch(sequence2, sequence1); // This runs the function based on the sequences inputted.
                input1 = 8; // This is so the loop can run again.
                continue; // This goes back to the loop after the funciton output.
            }
        }
        else if(input1 == 3){ // This runs if the user wants to identify mutations between two strands.
            string sequence1;
            string sequence2;
            bool validity = false;
            bool validity2 = false;

            while(validity == false){ // This runs until the user inputs a valid first sequence.
                cout << "Enter the first DNA sequence:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            while(validity2 == false){ // This runs until the user inputs a valid second sequence.
                cout << "Enter the second DNA sequence:" << endl;
                cin >> sequence2;
                validity2 = isValidStrand(sequence2); // This function checks the validity of the user inputted sequence.

                if(validity2 == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            identifyMutations(sequence1, sequence2); // This runs the function based on the sequences inputted.
            input1 = 8; // This is so the loop can run again.
            continue; // This goes back to the loop after the funciton output.
        }
        else if(input1 == 4){ // This runs if the user wants to transcribe DNA to RNA.
            string sequence1;
            bool validity = false;

            while(validity == false){ // This runs until the user inputs a valid sequence.
                cout << "Enter the DNA sequence to be transcribed:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            cout << "The transcribed DNA is: ";
            transcribeDNAtoRNA(sequence1); // This runs the function based on the sequences inputted.
            input1 = 8; // This is so the loop can run again.
            continue; // This goes back to the loop after the funciton output.
        }
        else if(input1 == 5){ // This runs if the user wants to find the reverse complement of a sequence.
            string sequence1;
            bool validity = false;

            while(validity == false){ // This runs until the user inputs a valid sequence.
                cout << "Enter the DNA sequence:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            cout << "The reverse complement is: "; 
            reverseComplement(sequence1); // This runs the function based on the sequences inputted.
            input1 = 8; // This is so the loop can run again.
            continue; // This goes back to the loop after the funciton output.
        }
        else if(input1 == 6){ // This runs if the user wants to find codons in their DNA sequence.
            string sequence1;
            bool validity = false;

            while(validity == false){ // This runs until the user inputs a valid sequence.
                cout << "Enter the DNA sequence:" << endl;
                cin >> sequence1;
                validity = isValidStrand(sequence1); // This function checks the validity of the user inputted sequence.

                if(validity == false){ // This runs if the string is not valid.
                    cout << "Invalid input. Please enter a valid sequence." << endl;
                }
            }

            cout << "The extracted reading frames are:" << endl;
            getCodingFrames(sequence1); // This runs the function based on the sequences inputted.
            input1 = 8; // This is so the loop can run again.
            continue; // This goes back to the loop after the funciton output.
        }
        else if(input1 == 7){ // This runs if the user wants to exit the program.
            cout << "Exiting program." << endl; 
            return 0; // This ends the main function.
        }
    }
    return 0;
}