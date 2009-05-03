#ifndef __UNIT_TESTS_ASSERTION_H__
#define __UNIT_TESTS_ASSERTION_H__

#define ASSERT(x) \
	do { \
		if (!(x)) { \
			errx(1,"ASSERTION FAILED (%s:%d): "#x, \
					__FILE__, __LINE__ ) ; \
		} \
	} while (0)


#endif
