#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);
  EXPECT_EQ(1,v2==v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(0, &v2 == &v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
 ASSERT_ANY_THROW(TDynamicVector<int> v(10); v[ - 1] = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(10); v[11] = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<TDynamicVector<int>> v(4);
	ASSERT_NO_THROW(v=v);
}


TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);
	for (int i = 0; i < size(v1); i++)
		v1[i] = 1;
	v2 = v1;
	EXPECT_EQ(1, v1 == v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(7);
	TDynamicVector<int> v2(10);
	for (int i = 0; i < size(v1); i++)
		v1[i] = 1;
	v2 = v1;
	EXPECT_TRUE( v1.size() == v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(7);
	TDynamicVector<int> v2(10);
	for (int i = 0; i < size(v1); i++)
		v1[i] = 1;
	v2 = v1;
	EXPECT_TRUE( v1 == v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr,4);
	TDynamicVector<int> b;
	b = a;
  EXPECT_TRUE(a==b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
  EXPECT_TRUE(a==a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector <int> a(5);
	TDynamicVector<int> b(4);

  EXPECT_TRUE(a!=b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	int res[4] = { 2,3,4,5 };
	TDynamicVector<int> c(res, 4);
  EXPECT_EQ(a+1,c);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	TDynamicVector<int> b = a - 1;
	int res[4] = { 0,1,2,3 };
	TDynamicVector<int> c(res, 4);
	EXPECT_EQ(a-1, c);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	int arrres[4] = { 2,4,6,8 };
	TDynamicVector<int> c(arrres, 4);
	EXPECT_EQ(a*2, c);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	int arr1[4] = { 3,6,8,9 };
	TDynamicVector<int> b(arr1, 4);
	int arres[4] = { 4,8,11,13 };
	TDynamicVector<int> res(arres, 4);
	EXPECT_EQ(a+b, res);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector <int> a(5);
	TDynamicVector<int> b(4);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	int arr1[4] = { 3,6,8,9 };
	TDynamicVector<int> b(arr1, 4);
	int arres[4] = { -2,-4,-5,-5 };
	TDynamicVector<int> res(arres, 4);
	EXPECT_EQ(a-b, res);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector <int> a(5);
	TDynamicVector<int> b(4);
	ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int arr[4] = { 1,2,3,4 };
	TDynamicVector <int> a(arr, 4);
	int arr1[4] = { 3,6,8,9 };
	TDynamicVector<int> b(arr1, 4);
	int res = 75;
	EXPECT_EQ(a*b, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector <int> a(5);
	TDynamicVector<int> b(4);
	ASSERT_ANY_THROW(a * b);
}

