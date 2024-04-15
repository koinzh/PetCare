# 若使用交叉编译，需要修改CC和AR
CC := gcc
AR := ar
BLD_CFLAGS := $(CFLAGS) -Wall -Werror 
BLD_CFLAGS += -Os -fPIC

# 路径定义
TOP_DIR := $(shell pwd)
DEMOS_DIR := demos
OUT_DIR := output
LIB_DIR := output/lib
INCLUDE_DIR := output/include
NOPOLL_DIR := external/nopoll/
BLD_LDFLAGS := $(LDFLAGS) -lpthread

# 设置默认链接路径为$(LIB_DIR)
LIB_LDFLAGS := -L $(LIB_DIR) -Wl,-rpath,$(LIB_DIR)

# 使用安全隧道/远程登录功能,才编译外部库nopoll
ra_exist = $(shell if [ -d $(NOPOLL_DIR) ]; then echo "true"; else echo "false"; fi)
ifeq ("$(ra_exist)", "true")
NOPOLL_SRC := $(shell find $(NOPOLL_DIR) -name "*.c")
NOPOLL_FILES := $(NOPOLL_SRC:.c=.o)
NOPOLL_FILES := $(addprefix $(OUT_DIR)/,$(NOPOLL_FILES))
NOPOLL_LIB := libnopoll
LIB_LDFLAGS += -lnopoll
STA_LIB_LDFLAGS += $(LIB_DIR)/libnopoll.a 
endif

# LinkSDK源码文件
HDR_DIR := $(shell find . -type d \( ! -name demos \))
BLD_CFLAGS += $(addprefix -I,$(HDR_DIR))
SRC_FILES := $(shell find . -not -path "*/demos/*.c" -not -path "*/nopoll/*" -name "*.c")
OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ_FILES := $(addprefix $(OUT_DIR)/,$(OBJ_FILES))
AIOT_LIB := libaiot

DYN_LIB_LDFLAGS := -laiot
DYN_LIB_LDFLAGS += $(LIB_LDFLAGS)
STA_LIB_LDFLAGS := $(LIB_DIR)/libaiot.a

# demo及头文件输出
PROG_TARGET := $(subst _,-,$(patsubst %.c,%,$(wildcard demos/*_demo.c)))
INCLUDE_SRC := $(shell find . -not -path "*/output/*.h" -name "aiot_*_api.h")

Q := @
all: prepare $(NOPOLL_LIB) $(AIOT_LIB) $(PROG_TARGET)

prepare:
	$(Q)mkdir -p $(OUT_DIR)
	$(Q)mkdir -p $(LIB_DIR)
	$(Q)mkdir -p $(INCLUDE_DIR)

$(NOPOLL_LIB): $(NOPOLL_FILES)
	$(Q)echo "+ Linking $(LIB_DIR)/$@.so ..."
	$(Q)$(CC) -fPIC -shared -o $(LIB_DIR)/$@.so $^
	$(Q)echo "+ Linking $(LIB_DIR)/$@.a ..."
	$(Q)$(AR) -cr $(LIB_DIR)/$@.a $^

$(AIOT_LIB): $(OBJ_FILES)
	$(Q)cp $(INCLUDE_SRC) $(INCLUDE_DIR)
	$(Q)echo "+ Linking $(LIB_DIR)/$@.so ..."
	$(Q)$(CC) -fPIC -shared -o $(LIB_DIR)/$@.so $^ $(LIB_LDFLAGS) $(BLD_LDFLAGS)
	$(Q)echo "+ Linking $(LIB_DIR)/$@.a ..."
	$(Q)$(AR) -cr $(LIB_DIR)/$@.a $^

$(PROG_TARGET): $(NOPOLL_lib) $(AIOT_LIB)
	$(Q)echo "+ Linking $(OUT_DIR)/$(notdir $@) ..."
	$(Q)mkdir -p $(dir $@)
	$(Q)if [ $(notdir $@) = "remote-access-basic-demo" ] \
		|| [ $(notdir $@) = "tunnel-basic-demo" ] ;then \
		$(CC) -o $@ \
			$(patsubst $(OUT_DIR)/%,%,$(addsuffix .c,$(subst $(notdir $@),$(subst -,_,$(notdir $@)),$@))) \
			$(BLD_CFLAGS) $(DYN_LIB_LDFLAGS) $(BLD_LDFLAGS); \
	else \
		$(CC) -o $@ \
			$(patsubst $(OUT_DIR)/%,%,$(addsuffix .c,$(subst $(notdir $@),$(subst -,_,$(notdir $@)),$@))) \
			$(BLD_CFLAGS) $(STA_LIB_LDFLAGS) $(BLD_LDFLAGS); \
	fi

	$(Q)mv $@ $(OUT_DIR)

$(OUT_DIR)/%.o: %.c
	$(Q)echo ": Compiling $< ..."
	$(Q)mkdir -p $(OUT_DIR)/$(dir $<)
	$(Q)$(CC) -o $@ -c $< $(BLD_CFLAGS)

clean:
	$(Q)rm -rf $(OUT_DIR)

