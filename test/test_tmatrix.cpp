#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	TDynamicMatrix<int> b = a;
	EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix <int> a;
	TDynamicMatrix <int> b(a);
  EXPECT_FALSE(&a==&b);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix <int> a(5);
	EXPECT_EQ(5, a.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix <int> a(5);
	a[1][1] = 5;
	EXPECT_EQ(5, a[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> a (5); a[1][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> a(5); a[1][6] = 0);

}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	ASSERT_NO_THROW(a = a);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	TDynamicMatrix<int> b(4);
	b = a;
  EXPECT_TRUE(a==b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	TDynamicMatrix<int> b(4);
	b = a;
	EXPECT_TRUE(a.size() == b.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	TDynamicMatrix<int> b(6);
	b = a;
	EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
	TDynamicMatrix<int> b(a);
  EXPECT_TRUE(a==b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> a(4);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			a[i][j] = 1;
		}
	}
  EXPECT_TRUE(a==a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix <int> a(5);
	TDynamicMatrix <int> b(4);
	EXPECT_FALSE(a==b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(3);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j <a.size(); j++)
			a[i][j] = 9;
	TDynamicMatrix<int> b(3);
	for (int i = 0; i < b.size(); i++)
		for (int j = 0; j < b.size(); j++)
			b[i][j] = 1;

	TDynamicMatrix<int> c(3);
	for (int i = 0; i < c.size(); i++)
		for (int j = 0; j < c.size(); j++)
			c[i][j] = 10;
	EXPECT_EQ(c, a + b);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix <int> a(5);
	TDynamicMatrix<int> b(4);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(3);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a.size(); j++)
			a[i][j] = 9;
	TDynamicMatrix<int> b(3);
	for (int i = 0; i < b.size(); i++)
		for (int j = 0; j < b.size(); j++)
			b[i][j] = 9;

	TDynamicMatrix<int> c(3);
	for (int i = 0; i < c.size(); i++)
		for (int j = 0; j < c.size(); j++)
			c[i][j] = 0;
	EXPECT_EQ(c, a - b);
	
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix <int> a(5);
	TDynamicMatrix<int> b(4);
	ASSERT_ANY_THROW(a - b);
}

