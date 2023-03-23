#include <algorithm>
#include <set>

namespace my_namespace {

static std::string getName(const myNode* n) {
  return n ? n->getName() : std::string("(nil)");
}

Table::~Table() {
  BOOST_FOREACH (TableInst* tableInst, tables) {
    if (tableInst) {
      delete tableInst;
    }
  }
  END_BOOST_FOREACH;
}

bool Table::add(const myNode* node,
                const myNode* nodePointer,
                const Value&  value,
                unsigned int  source,
                bool sadPrecedence, // set_precedence value for checking in
                                    // whole hierachy
                int level) {
  if (!done) {
    if (!inValid) {
      assert(false);

      if (instance().getAttr("err")) {
        std::cout("ERR_001", __LINE__);
      }
      return false;
    }
    initialize(level);
  }

  unsigned int index = node->getParent();
  if (index < tables.size()) {
    if (tables[index]) {
      return tables[index]->set(
          nodePointer, node, value, value, source, sadPrecedence, level);
    }
  }

  if (instance().getAttr("err")) {

    const myList* context = _db->getlist();

    const myInst* inst = node->getInst();

    std::cout(
        "NOTE_00014", inst->getName(context), index, tables.size(), __LINE__);
  }
  return !value.isNull();
}

void Table::advance(int count) {
  if (count > 0) {
    while (count-- > 0) {
      ++_iter;
    }

  } else if (count < 0) {
    while (count++ < 0) {
      --_iter;
    }
  }
}

} // namespace my_namespace
