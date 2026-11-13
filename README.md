# cpp-text-concordance
A C++ program that builds a text concordance from a text file using binary search trees. 

## Features

- Reads a text file and tracks each word's frequency
- Records the line where each word first appears
- Searches for a word
- Displays the concordance in alphabetical order

## Implementation

Words are stored in binary search trees, grouped by their first letter. Each entry records the word, its number of occurrences, and its first line number.

## Build and run

Open the Visual Studio solution in Visual Studio with C++ desktop development tools installed, then build and run the project.

When prompted, enter the path to the text file you want to analyze.
