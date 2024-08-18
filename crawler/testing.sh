# no arguments
echo "No arguments"
'./crawler'

# external server
echo "External server"
./crawler https://www.google.com testing 1

# invalid depths 
echo "Invalid depths"                                                                
./crawler hhttp://cs50tse.cs.dartmouth.edu/tse/letters/index.html pageDirectory -1                                                                          
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html pageDirectory 11 

# non-existent directory
echo "Non-existent directory"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html test 1

# excessive many arguments
echo "Excessive many arguments"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html pageDirectory 1 test


# valid test
echo "Valid test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html pageDirectory 2

# valid test & different seed
echo "Valid test & different seed"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/A.html pageDirectory 3
