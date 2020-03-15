#ifndef DCVM_BASE_DCVM_DEFINES_HPP_
#define DCVM_BASE_DCVM_DEFINES_HPP_

#ifndef UNREFFERENCE_VARIABLE
#define UNREFFERENCE_VARIABLE(x) x
#endif

#ifndef DCVM_NO_EXCEPTIONS
#define DCVM_BEGIN_CATCH_HANDLER try {

#define DCVM_END_CATCH_HANDLER                      \
}                                                   \
catch (std::exception&) {                           \
    DCVM_INFO_TRACE("Exceptions has been thrown."); \
    return DCVM_ERR_INTERNAL;                       \
}

#define DCVM_END_CATCH_HANDLER_NO_RETURN            \
}                                                   \
catch (std::exception&) {                           \
    DCVM_INFO_TRACE("Exceptions has been thrown."); \
}

#else
#define DCVM_BEGIN_CATCH_HANDLER
#define DCVM_END_CATCH_HANDLER
#define DCVM_END_CATCH_HANDLER_NO_RETURN
#endif

#endif