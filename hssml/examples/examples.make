HSSML = ./build/hssml/hssml
WORK_DIR = ./hssml/examples
BUILD_DIR = ./build/examples

all: simple_website

simple_website: $(BUILD_DIR)/simple_website
	$(HSSML) $(WORK_DIR)/simple_website/index.scss $(BUILD_DIR)/simple_website/index.html

$(BUILD_DIR)/simple_website:
	mkdir $(BUILD_DIR)/simple_website