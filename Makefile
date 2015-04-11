all: list_test list_test_st

list_test: list_test.c 
	gcc list_test.c -o list_test

list_test_st: list_test_st.c 
	gcc list_test_st.c -o list_test_st

clean:
	rm -f list_test list_test_st
