#include <come-pcre.h>

int main()
{
    xassert("char_match test", "ABC".match("A".to_regex(), null));
    xassert("char_index test", "ABC".index("B", -1) == 1);
    xassert("char_rindex test", "ABCABC".rindex("B", -1) == 4);
    xassert("char_index_regex", "ABC".index_regex("B".to_regex(), -1) == 1);
    xassert("char_rindex_regex", "ABCABC".rindex_regex("B".to_regex(), -1) == 4);

    string str = string("ABC");

    str.replace(1, 'C');

    xassert("char_replace", strcmp(str, "ACC") == 0);
    xassert("char_multiply", strcmp(string("ABC").multiply(2), "ABCABC") == 0);

    xassert("char_sub", strcmp("ABC".sub("B".to_regex(), "C", null), "ACC") == 0);

    auto li = "ABC".scan(".".to_regex());

    xassert("char_scan", strcmp(li.item(0, null), "A") == 0 && strcmp(li.item(1, null), "B") == 0 && strcmp(li.item(2, null), "C") == 0);

    auto li2 = "A,B,C".split(",".to_regex());

    xassert("char_split", strcmp(li2.item(0, null), "A") == 0 && strcmp(li2.item(1, null), "B") == 0 && strcmp(li2.item(2, null), "C") == 0);

    auto li3 = "A,B,C".split_char(',');

    xassert("char_split_char", strcmp(li3.item(0, null), "A") == 0 && strcmp(li3.item(1, null), "B") == 0 && strcmp(li3.item(2, null), "C") == 0);

    xassert("char_delete", string("ABC").delete(0,1).equals("BC"));

    xassert("wchar_substring", wcscmp(wstring("ABC").substring(0,1), wstring("A")) == 0);

    return 0;
}
