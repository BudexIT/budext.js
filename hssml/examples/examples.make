ifeq ($(OS), Windows_NT)
HSSML = build\hssml\hssml.exe
WORK_DIR = hssml/examples
BUILD_DIR = build/examples
else
HSSML = ./build/hssml/hssml
WORK_DIR = ./hssml/examples
BUILD_DIR = ./build/examples
endif

all: simple_website

simple_website: $(BUILD_DIR)/simple_website
	$(HSSML) $(WORK_DIR)/simple_website/index.scss $(BUILD_DIR)/simple_website/index.html

$(BUILD_DIR)/simple_website: $(BUILD_DIR)
	mkdir $(BUILD_DIR)/simple_website


$(BUILD_DIR):
	mkdir $(BUILD_DIR)