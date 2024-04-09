target("arr")
    set_kind("binary")
    add_files("./container/test/seq_list_test.cpp")

target("node")
    set_kind("binary")
    add_files("./container/test/linked_list_test.cpp")

target("stack")
    set_kind("binary")
    add_files("./container/test/stack_and_queqe_test.cpp")

target("tree")
    set_kind("binary")
    add_files("./graph/test/tree_test.cpp")