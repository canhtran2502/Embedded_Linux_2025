
PRJ_NAME := book_program
LIB_NAME := book

PRO_DIR := .
BIN_DIR := ${PRO_DIR}/bin
INC_DIR := ${PRO_DIR}/inc
OBJ_DIR := ${PRO_DIR}/obj
SRC_DIR := ${PRO_DIR}/src

LIB_DIR := ${PRO_DIR}/lib
LIB_SHARE_DIR := ${LIB_DIR}/shared
LIB_STATIC_DIR := ${LIB_DIR}/static

CC := gcc
SHARED_CFLAGS := -fPIC
CFLAGS  := -I ${INC_DIR}

# List of source files and object files
SRC_FILES := ${SRC_DIR}/english.c ${SRC_DIR}/math.c ${SRC_DIR}/main.c
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@echo "Compiling $<"
	${CC} -c $< ${CFLAGS} -o $@

create_object: ${OBJ_FILES}

create_shared_library: ${OBJ_FILES}
	@echo "Create shared library"
	${CC} -shared ${OBJ_FILES} -o ${LIB_SHARE_DIR}/lib${LIB_NAME}.so

create_static_library: ${OBJ_FILES}
	@echo "Create static library"
	ar crv ${LIB_STATIC_DIR}/lib${LIB_NAME}.a ${OBJ_FILES}

create_shared_lib_program: create_shared_library
	@echo "Create program with shared library"
	${CC} -o ${BIN_DIR}/${PRJ_NAME} ${SRC_DIR}/main.c -L${LIB_SHARE_DIR} -l${LIB_NAME} ${CFLAGS}

install:
	@echo "Install shared library - May need sudo permision"
	install ${LIB_SHARE_DIR}/lib${LIB_NAME}.so /usr/lib

create_static_lib_program: create_static_library
	@echo "Create program with static library"
	${CC} -o ${BIN_DIR}/${PRJ_NAME} ${SRC_DIR}/main.c -L${LIB_STATIC_DIR} -l${LIB_NAME} ${CFLAGS}


all: 
	@echo "Compile and links the program directly without static/shared library"
	${CC} ${SRC_DIR}/* -o ${BIN_DIR}/${PRJ_NAME} ${CFLAGS}

#Homework Information 
info: 
	@echo "This is Canh Tran's homework."
	@echo "It includes both static and shared library."
	@echo "For shared library, because we need to install to run binary program, please use sudo permision to run \"make\""

#Clean target (remove objects file, binary, library)
clean: 
	rm -rf ${OBJ_DIR}/*.o 
	rm -rf ${BIN_DIR}/${PRJ_NAME}
	rm -rf ${LIB_SHARE_DIR}/*.so 
	rm -rf $(LIB_STATIC_DIR)/*.a
