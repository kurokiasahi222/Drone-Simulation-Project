CXX = g++
CXXFLAGS = -std=c++17 -g -Wl,-rpath,$(DEP_DIR)/lib
ROOT_DIR = $(shell pwd)
DEP_DIR = $(ROOT_DIR)/dependencies

-include $(DEP_DIR)/env

# need to use different version based on libssl
WEBSOCKET_VERSION_MAJOR:=$(shell pkg-config --modversion libssl | cut -d '.' -f 1)
ifeq "$(WEBSOCKET_VERSION_MAJOR)" "3"
	WEBSOCKETS = websockets22
else
	WEBSOCKETS = websockets20
endif

make-depend-cxx = $(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $(INCLUDES) $1

export CXX CXXFLAGS ROOT_DIR DEP_DIR WEBSOCKETS make-depend-cxx

BUILD_DIR = build
TRANSITE_EXE = $(BUILD_DIR)/bin/transit_service


PORT = 8081

.PHONY: all routing transit transit_service clean run docs lint

all: transit_service

run:
ifeq	(,$(wildcard $(TRANSITE_EXE)))
	$(MAKE) -j
endif
	./$(TRANSITE_EXE) $(PORT) apps/transit_service/web

$(BUILD_DIR):
	mkdir -p $@

routing: $(BUILD_DIR)
	$(MAKE) -C libs/routing

transit: $(BUILD_DIR) routing
	$(MAKE) -C libs/transit

transit_service: $(BUILD_DIR) routing transit
	$(MAKE) -C apps/transit_service

$(TRANSITE_EXE): transit_service

clean:
	rm -rf $(BUILD_DIR)

docs:
	cd docs; doxygen Doxyfile; cd ..;

lint:
	cpplint --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit,-build/header_guard,-runtime/references,-runtime/threadsafe_fn ./libs/transit/src/*.cc ./libs/transit/include/*.h