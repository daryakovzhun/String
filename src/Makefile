CC=gcc
CFLAGS=-Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
DIR_OUT=../s21_string/
SRCS = s21_memchr.c \
	s21_memcmp.c \
	s21_memcpy.c \
	s21_memmove.c \
	s21_memset.c \
	s21_strcat.c \
	s21_strchr.c \
	s21_strcmp.c \
	s21_strncmp.c \
	s21_strcpy.c \
	s21_strcspn.c \
	s21_strerror.c \
	s21_strlen.c \
	s21_strncat.c \
	s21_strncpy.c \
	s21_strpbrk.c \
	s21_strrchr.c \
	s21_strspn.c \
	s21_strstr.c \
	s21_strtok.c \
	s21_to_upper.c \
	s21_to_lower.c \
	s21_insert.c \
	s21_trim.c \
	s21_atoi.c \
	s21_ftoa.c \
	s21_itoa.c \
	s21_itoau.c \
	s21_sprintf.c \
	# s21_string_test.c
OBJS = $(SRCS:.c=.o)
NAME = test
REPORT_NAME = report


all: s21_string.a gcov_report test

test: $(OBJS) s21_string_test.c
	$(CC) $(CFLAGS) $(CHECK_FLAGS) s21_string_test.c $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) *.o *.gcno *.gcda *.info *.a $(REPORT_NAME) $(NAME) check_res

s21_string.a: $(OBJS)
	ar rc s21_string.a $(OBJS) 
	ranlib s21_string.a

gcov_report: s21_string_test.c
#   checkmk test.check > s21_string_test.c
	$(CC) -o $(NAME) $(SRCS) s21_string_test.c $(ALL_FLAGS) 
	./$(NAME)
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o finish
