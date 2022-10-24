// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_size_clear_pop_front_back) {

    List<int> empty_list;
    List<double> single_item_list;
    List<int> new_list;

    single_item_list.push_front(1.7);
    new_list.push_front(1);
    new_list.push_front(2);
    new_list.push_front(3);
    new_list.push_front(4);
    new_list.push_front(5);

    ASSERT_EQUAL(empty_list.size(), 0);
    ASSERT_EQUAL(single_item_list.size(), 1);
    ASSERT_EQUAL(new_list.size(), 5);

    single_item_list.pop_front();
    ASSERT_TRUE(single_item_list.empty());
    single_item_list.push_front(5.5);
    ASSERT_EQUAL(single_item_list.front(), single_item_list.back());
    single_item_list.pop_back();
    ASSERT_TRUE(single_item_list.empty());

    ASSERT_EQUAL(new_list.front(), 5);
    new_list.pop_front();
    ASSERT_EQUAL(new_list.front(), 4);
    ASSERT_EQUAL(new_list.back(), 1);

    new_list.pop_back();
    ASSERT_EQUAL(new_list.size(), 3);
    ASSERT_EQUAL(new_list.back(), 2);

    new_list.clear();
    ASSERT_TRUE(new_list.empty());

}

TEST(test_push_front_back) {
    List<std::string> new_list;
    List<std::string> empty_list;

    new_list.push_front("hello");
    new_list.push_back("beautiful");
    new_list.push_back("world");
    ASSERT_EQUAL(new_list.back(), "world");
    ASSERT_EQUAL(new_list.front(), "hello");

    empty_list.push_front("");
    empty_list.push_back("");
    ASSERT_EQUAL(empty_list.back(), "");
    ASSERT_EQUAL(empty_list.front(), "");

    //ASSERT_TRUE(true);
}

TEST(test_create_copy_assign) {

    List<int> new_list;
    List<int> empty_list;
    empty_list = new_list;
    
    ASSERT_EQUAL(new_list.size(), 0);
    ASSERT_EQUAL(new_list.size(), empty_list.size());

    new_list.push_front(7);
    List<int> new_list_1;
    new_list_1 = new_list;
    ASSERT_EQUAL(new_list.size(), new_list_1.size());
    ASSERT_EQUAL(new_list.front(), new_list_1.back());

    new_list.push_front(11);

    List<int> new_list2;
    new_list2 = new_list;
    ASSERT_EQUAL(new_list.front(), new_list2.front());
    ASSERT_EQUAL(new_list.back(), new_list2.back());

    new_list.push_front(5);
    //ASSERT_TRUE(true);

    List<int> new_list3(new_list);
    ASSERT_EQUAL(new_list.front(), new_list3.front());
    ASSERT_EQUAL(new_list.back(), new_list3.back());
    ASSERT_NOT_EQUAL(new_list.front(), new_list2.front());

    new_list.clear();
    new_list_1.clear();
    new_list2.clear();
    new_list3.clear();
    ASSERT_TRUE(new_list.empty());
    ASSERT_TRUE(new_list_1.empty());
    ASSERT_TRUE(new_list2.empty());
    ASSERT_TRUE(new_list3.empty());

    //ASSERT_TRUE(true);
}


TEST(test_Iterator) {

    List<int> new_list;

    new_list.push_front(1);
    new_list.push_front(2);
    new_list.push_back(5);
    new_list.push_back(5);
    new_list.push_back(5);
    new_list.push_front(7);
    //ASSERT_TRUE(true);

    List<int>::Iterator iter_b_1 = new_list.begin();
    new_list.insert(iter_b_1, 4);
    iter_b_1 = new_list.begin();
    new_list.erase(iter_b_1);
    iter_b_1 = new_list.begin();

    List<int>::Iterator iter_e_1 = new_list.end();
    const List<int>::Iterator iter_e_2 = iter_e_1;

    ASSERT_TRUE(iter_b_1 != iter_e_1);
    ASSERT_EQUAL(*iter_b_1, 7);
    ++iter_b_1;
    ASSERT_EQUAL(*iter_b_1, 2);

    --iter_b_1;
    ASSERT_EQUAL(*iter_b_1, 7);

    List<int> new_list1;
    List<int>::Iterator iter_b_2 = new_list1.begin();
    new_list1.insert(iter_b_2, 5);
    iter_b_2 = new_list1.begin();
    new_list1.erase(iter_b_2);
    iter_b_2 = new_list1.begin();

    List<int>::Iterator iter_e = new_list1.begin();
    const List<int>::Iterator iter_e_3 = iter_e;

    ASSERT_TRUE(iter_b_2 == iter_e);
}

TEST(test_full_List_operations) {
    List<int> new_list;

    int size = 0;
    new_list.empty();
    new_list.size();
    ASSERT_EQUAL(new_list.size(), size);

    new_list.push_back(42);
    new_list.push_front(42);

    new_list.front() = 73;
    new_list.back() = 73;

    new_list.pop_front();
    new_list.pop_back();

    List<int> new_list2(new_list);
    new_list2 = new_list;

    List<int>::Iterator iter = new_list.begin();
    new_list.insert(iter, 42);
    iter = new_list.begin();
    new_list.erase(iter);
    iter = new_list.begin();

    List<int>::Iterator iter2 = new_list.end();
    const List<int>::Iterator iter3 = iter2;

    ASSERT_TRUE(iter == iter2);
    ASSERT_TRUE(iter3 == new_list.end());
    ASSERT_TRUE(new_list.end() == iter3);

    new_list.push_front(42);
    new_list.push_back(42);
    iter = new_list.begin();
    ASSERT_TRUE(iter != iter2);

    ASSERT_FALSE(iter3 != new_list.end());
    ASSERT_FALSE(new_list.end() != iter3);
    ++iter;
    ASSERT_EQUAL(*iter, 42);


    List<int>::Iterator iter_cpy(iter);
    iter_cpy = iter;
    ++--iter;
    ASSERT_EQUAL(*iter, 42);
    *--++new_list.begin();
    ASSERT_EQUAL(*new_list.begin(), 42);


    new_list.insert(new_list.begin(), 3);
    new_list.erase(new_list.begin());

    List<int> new_new_list3;
    new_new_list3.push_back(3);
    ASSERT_EQUAL(new_new_list3.size(), 1);

    List<int> new_list4;
    new_list4.push_back(4);
    new_list4.push_back(14);
    ASSERT_EQUAL(new_list4.size(), 2);

    new_list.clear();
}

TEST(erase) {
    List<int> new_list;

    new_list.push_back(1);
    new_list.push_back(2);
    new_list.push_back(3);

    List<int>::Iterator iter1 = new_list.begin();
    
    new_list.erase(iter1);

    ASSERT_EQUAL(new_list.front(), 2);
    ASSERT_EQUAL(new_list.back(), 3);
    iter1 = new_list.begin();
    ++iter1;

    new_list.erase(iter1);

    ASSERT_FALSE(new_list.empty());
}

TEST(erase_to_empty) {
    List<int> new_list;

    new_list.push_back(1);

    List<int>::Iterator iter1 = new_list.begin();

    new_list.erase(iter1);

    ASSERT_TRUE(new_list.empty());

}

TEST(erase_2) {
    List<int> new_list;

    new_list.push_front(1);
    new_list.push_front(2);
    new_list.push_front(3);

    List<int>::Iterator iter1 = new_list.begin();

    ++iter1;

    new_list.erase(iter1);

    ASSERT_EQUAL(new_list.front(), 3);
    ASSERT_EQUAL(new_list.back(), 1);
}

TEST(insert) {
    List<int> new_list;

    List<int>::Iterator iter1 = new_list.end();

    new_list.insert(iter1, 1);

    ASSERT_EQUAL(new_list.front(), 1);
    ASSERT_EQUAL(new_list.back(), 1);

    iter1 = new_list.begin();

    new_list.insert(iter1, 2);

    ASSERT_EQUAL(new_list.front(), 2);
    ASSERT_EQUAL(new_list.back(), 1);

    new_list.insert(iter1, 3);

    ASSERT_EQUAL(new_list.size(), 3);

}

TEST(insert_2) {
    List<int> new_list;

    List<int>::Iterator iter1 = new_list.end();

    new_list.insert(iter1, 3);

    iter1 = new_list.begin();

    new_list.insert(iter1, 2);

    iter1 = new_list.begin();

    new_list.insert(iter1, 1);

    iter1 = new_list.begin();

    ASSERT_TRUE(!new_list.empty());
    ASSERT_EQUAL(new_list.size(), 3);
    ASSERT_EQUAL(new_list.front(), 1);
    ASSERT_EQUAL(new_list.back(), 3);

    ++iter1;
    new_list.insert(iter1, 4);
    ASSERT_NOT_EQUAL(new_list.front(), 4);
}

TEST(test_pop_empty) {
    List<int> new_list;

    new_list.push_front(1);
    new_list.pop_front();

    ASSERT_TRUE(new_list.empty());

}

TEST(front_and_back) {
    List<int> new_list;

    new_list.push_back(1);

    ASSERT_EQUAL(new_list.front(), 1);
    ASSERT_EQUAL(new_list.back(), 1);

}

TEST_MAIN()