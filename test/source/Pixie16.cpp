//
// Created by Vetle Wegner Ingeberg on 10/02/2021.
//

#include <doctest/doctest.h>
#include <Pixie16/pixie16app_export.h>

TEST_CASE("Initialize") {

    unsigned short Num = 7;
    unsigned short PXImap[] = {2, 3, 4, 5, 6, 7, 8};

    int ret = Pixie16InitSystem(Num, PXImap, 0);

    CHECK(ret != 0);

}