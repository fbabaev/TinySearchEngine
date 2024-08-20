# Test with no arguments to check error handling
./indexer

# Test with only one argument to check error handling
./indexer arg1

# Test with three arguments to ensure no excess arguments are accepted
./indexer arg1 arg2 arg3

# Test with invalid file directory to confirm error handling
./indexer firdavs testing

# Test with valid file directory but no crawler data available
mkdir testingdir
./indexer testingdir test
rmdir testingdir

# Test invalid pageDirectory which is not a crawler directory
mkdir not_a_crawler_dir
touch not_a_crawler_dir/non_webpage_file
./indexer not_a_crawler_dir test
rm -r not_a_crawler_dir

# Test inability to write to file due to permission restrictions
echo "Sample file content" > file_test
chmod ugo=rx file_test
./indexer ../crawler/pageDirectory file_test
chmod ugo=rwx file_test
cat file_test
rm file_test -f

# Testing writable file handling by indextest
echo '' > file_test
chmod ugo=rwx file_test
./indextest testoutput file_test
cat file_test
rm file_test -f

# Valid test case to ensure proper functionality
./indexer ../crawler/pageDirectory test

# Run valgrind to check for memory leaks and errors on indexer
valgrind --leak-check=full ./indexer ../crawler/pageDirectory test

# Run valgrind to check for memory leaks and errors on indextest
valgrind --leak-check=full ./indextest test testoutput
