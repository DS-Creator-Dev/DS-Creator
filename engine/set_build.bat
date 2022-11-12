@goto action_%1
@goto end

:action_testmod
@copy Makefile_test Makefile
@goto end

:action_normal
@copy Makefile_normal Makefile
:end