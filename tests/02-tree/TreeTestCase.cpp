//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"
#include <iostream>
using boost::filesystem::exists;
using boost::filesystem::is_directory;
using boost::filesystem::path;
using boost::filesystem::directory_iterator;


TEST_F(TreeTestCase, test1) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    FileNode answer;
    answer.name = boost::filesystem::path(path).filename().string();
    answer.is_dir = true;
    ASSERT_NO_THROW(GetTree(path, true));
    ASSERT_TRUE(GetTree(path, true) == answer);
    boost::filesystem::remove_all(path);
}


TEST_F(TreeTestCase, test2) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    ASSERT_THROW(GetTree(path + "/5", true), std::invalid_argument);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, test20) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);

    std::string path2 = path + "/test";
    boost::filesystem::create_directory(path2);

    FileNode answer;
    answer.name = boost::filesystem::path(path).filename().string();
    answer.is_dir = true;
    answer.children.push_back({boost::filesystem::path(path2).filename().string(), true, {}});
    ASSERT_TRUE(GetTree(path, true) == answer);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, test3) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    std::string filename = path + "/test.txt";
    std::ofstream fout(filename);
    fout << "1";
    fout.close();

    ASSERT_THROW(GetTree(filename, true), std::invalid_argument);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, test4) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    std::string filename = path + "/test.txt";
    std::ofstream fout(filename);
    fout << "1";
    fout.close();
    FileNode answer;
    answer.name = boost::filesystem::path(path).filename().string();
    answer.is_dir = true;
    answer.children.push_back({boost::filesystem::path(filename).filename().string(), false, {}});
    ASSERT_TRUE(GetTree(path, false) == answer);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, test5) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    std::string filename = path + "/test.txt";
    std::ofstream fout(filename);
    fout << "1";
    fout.close();

    FileNode answer;
    answer.name = boost::filesystem::path(path).filename().string();
    answer.is_dir = true;
    //answer.children.push_back({boost::filesystem::path(filename).filename().string(), false, {}});
    ASSERT_TRUE(GetTree(path, true) == answer);
    boost::filesystem::remove_all(path);
}


TEST_F(TreeTestCase, emptyNodesTest1) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    std::string filename = path + "/test.txt";
    std::ofstream fout(filename);
    fout << "1";
    fout.close();

    FileNode answer = GetTree(path, false);

    FileNode copy = answer;
    FilterEmptyNodes(answer, boost::filesystem::current_path());
    ASSERT_TRUE(copy == answer);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, emptyNodesTest2) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);

    std::string path2 = path + "/test2";
    boost::filesystem::create_directory(path2);

    FileNode node = GetTree(path2, false);

    FileNode answer({boost::filesystem::path(path).filename().string(), true, {}});
    FilterEmptyNodes(GetTree(path2, false), boost::filesystem::path(path2));
    ASSERT_TRUE(GetTree(path, false) == answer);
    boost::filesystem::remove_all(path);
}

TEST_F(TreeTestCase, emptyNodesTest3) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);
    std::string filename = path + "/test.txt";
    std::ofstream fout(filename);
    fout << "1";
    fout.close();

    FileNode answer = GetTree(path, false);

    FileNode copy = answer;
    FilterEmptyNodes(answer.children[0], boost::filesystem::path(filename));
    ASSERT_TRUE(copy == answer);
    boost::filesystem::remove_all(path);
}


TEST_F(TreeTestCase, equalTest1) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);

    std::string path2 = boost::filesystem::current_path().string() + "/test2";
    boost::filesystem::create_directory(path2);

    FileNode node1 = GetTree(path, true);
    FileNode node2 = GetTree(path2, true);
    ASSERT_FALSE(node1 == node2);
    boost::filesystem::remove_all(path);

    boost::filesystem::remove_all(path2);
}

TEST_F(TreeTestCase, equalTest2) {
    std::string path = boost::filesystem::current_path().string() + "/test";
    boost::filesystem::create_directory(path);

    std::string path2 = boost::filesystem::current_path().string() + "/test2";
    boost::filesystem::create_directory(path2);

    FileNode node1 = GetTree(path, true);
    FileNode node2 = node1;
    node2.is_dir = false;
    ASSERT_FALSE(node1 == node2);
    boost::filesystem::remove_all(path);
    boost::filesystem::remove_all(path2);
}