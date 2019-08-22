#include <map>
#include <memory>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "debug_util/debug_util.hpp"

class VarDBHelper : public VarDB {
 public:
  using VarDB::db_;
};

class VarDBTest : public ::testing::Test {
 public:
  virtual void SetUp() {
    var_db_ptr = std::unique_ptr<VarDBHelper>(new VarDBHelper);
  }

  virtual void TearDown() {}

  std::unique_ptr<VarDBHelper> var_db_ptr = nullptr;
};

TEST_F(VarDBTest, Append_normal) {
  std::vector<std::tuple<std::string, int>> input = {
      std::make_tuple("a", 1), std::make_tuple("a", 2), std::make_tuple("a", 2),
      std::make_tuple("a", 3), std::make_tuple("a", 3), std::make_tuple("a", 3),
  };
  for (auto& v : input) {
    std::string var_name = std::get<0>(v);
    int var_value        = std::get<1>(v);
    var_db_ptr->Append(var_name, std::to_string(var_value));
  }
  EXPECT_EQ(1, var_db_ptr->db_["a"]["1"]);
  EXPECT_EQ(2, var_db_ptr->db_["a"]["2"]);
  EXPECT_EQ(3, var_db_ptr->db_["a"]["3"]);
}

TEST_F(VarDBTest, Clear_normal) {
  var_db_ptr->Append("a", "1");
  EXPECT_NE("", var_db_ptr->ToString());
  var_db_ptr->Clear();
  EXPECT_EQ("", var_db_ptr->ToString());
  var_db_ptr->Clear();
  EXPECT_EQ("", var_db_ptr->ToString());
}

TEST_F(VarDBTest, ToString_normal) {
  EXPECT_EQ("", var_db_ptr->ToString());
  var_db_ptr->Append("a", "1");
  var_db_ptr->Append("b", "2");
  var_db_ptr->Append("b", "2");
  EXPECT_EQ("a[1]=1\nb[2]=2\n", var_db_ptr->ToString());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
