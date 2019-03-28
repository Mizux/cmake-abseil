PROJECT := abseil
BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
SHA1 := $(shell git rev-parse --verify HEAD)

# General commands
.PHONY: help
RESET=\e[0m
BOLD=\e[1m

help:
	@echo -e "${BOLD}SYNOPSIS${RESET}"
	@echo -e "\tmake <target> [NOCACHE=1]"
	@echo
	@echo -e "${BOLD}DESCRIPTION${RESET}"
	@echo -e "\ttest build inside docker containers so we can test against various major distro setup."
	@echo
	@echo -e "${BOLD}MAKE TARGETS${RESET}"
	@echo -e "\t${BOLD}help${RESET}: display this help and exit"
	@echo
	@echo -e "\t${BOLD}docker${RESET}: generate all docker devel images"
	@echo -e "\t${BOLD}docker_<distro>${RESET}: generate docker devel images for the specified distro"
	@echo
	@echo -e "\t${BOLD}configure${RESET}: cmake 'configure' using all devel image containers"
	@echo -e "\t${BOLD}configure_<distro>${RESET}: cmake 'configure' using the devel image container specified"
	@echo
	@echo -e "\t${BOLD}build${RESET}: cmake 'build' target ${BOLD}all${RESET} using all the devel image containers"
	@echo -e "\t${BOLD}build_<distro>${RESET}: cmake 'build' target ${BOLD}all${RESET} using the devel image container specified"
	@echo
	@echo -e "\t${BOLD}test${RESET}: cmake 'build' target ${BOLD}test${RESET} using all devel image containers"
	@echo -e "\t${BOLD}test_<distro>${RESET}: cmake 'build' target ${BOLD}test${RESET} using the devel image container specified"
	@echo
	@echo -e "\t${BOLD}install${RESET}: execute the cmake target ${BOLD}install${RESET} using all devel image container, then create an install image with it"
	@echo -e "\t${BOLD}install_<distro>${RESET}: execute the cmake target ${BOLD}install${RESET} using the devel image container specified, then create an install image with it"
	@echo
	@echo -e "\t${BOLD}test_install${RESET}: configure, build, test a sample project against it using all ${BOLD}install${RESET} image containers"
	@echo -e "\t${BOLD}test_install_<distro>${RESET}: configure, build, test a sample project against it using the ${BOLD}install${RESET} image container specified"
	@echo
	@echo -e "\t${BOLD}clean${RESET}: Remove build directories and log files for all distros"
	@echo -e "\t${BOLD}clean_<distro>${RESET}: Remove build directories and log files for the distro specified"
	@echo
	@echo -e "\t${BOLD}distclean${RESET}: execute ${BOLD}clean${RESET} and also remove all docker images"
	@echo -e "\t${BOLD}distclean_<distro>${RESET}: execute ${BOLD}clean_<distro>${RESET} and also remove the docker images"
	@echo
	@echo -e "\t${BOLD}<distro>${RESET}:"
	@echo -e "\t\t${BOLD}alpine${RESET} (latest)"
	@echo -e "\t\t${BOLD}archlinux${RESET} (latest)"
	@echo -e "\t\t${BOLD}centos${RESET} (latest)"
	@echo -e "\t\t${BOLD}fedora${RESET} (latest)"
	@echo -e "\t\t${BOLD}opensuse${RESET} (latest)"
	@echo -e "\t\t${BOLD}debian${RESET} (latest)"
	@echo -e "\t\t${BOLD}ubuntu${RESET} (latest)"
	@echo -e "\t\t${BOLD}xenial${RESET} (Ubuntu 16.04 LTS)"
	@echo -e "\te.g. 'make test_ubuntu'"
	@echo
	@echo -e "\tNOCACHE=1: use 'docker build --no-cache' when building container"
	@echo
	@echo -e "${BOLD}NOTES${RESET}"
	@echo -e "\tAll generated code will be located in the cache/ folder, use distclean to remove it"
	@echo
	@echo -e "branch: $(BRANCH)"
	@echo -e "sha1: $(SHA1)"

# Need to add cmd_distro to PHONY otherwise target are ignored since they do not
# contain recipe (using FORCE do not work here)
.PHONY: all
all: build

# Delete all implicit rules to speed up makefile
.SUFFIXES:
# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =
# Keep all intermediate files
# ToDo: try to remove it later
.SECONDARY:

# Docker image name
IMAGE := cmake_${PROJECT}

ifdef NOCACHE
DOCKER_BUILD_CMD := docker build --no-cache
else
DOCKER_BUILD_CMD := docker build
endif

# Use host user id instead of default root:root
UID := $(shell id -u)
GID := $(shell id -g)
DOCKER_DEVEL_CMD := docker run --rm -it -v ${PWD}/..:/project -w /project --user ${UID}:${GID}
#DOCKER_DEVEL_CMD := docker run --rm -it -v ${PWD}:/project -w /project

DOCKER_INSTALL_CMD := docker run --rm -it -v ${PWD}/sample:/project -w /project

DISTROS = alpine archlinux centos fedora opensuse debian ubuntu xenial

# $* stem
# $< first prerequist
# $@ target name

# DOCKER
targets = $(addprefix docker_, $(DISTROS))
.PHONY: docker $(targets)
docker: $(targets)
$(targets): docker_%: cache/%/docker_devel.tar
cache/%/docker_devel.tar: docker/%/Dockerfile
	mkdir -p cache/$*
	@docker image rm -f ${IMAGE}_$*:devel 2>/dev/null
	@rm -f $@
	${DOCKER_BUILD_CMD} -t ${IMAGE}_$*:devel -f $< docker/$*
	docker save ${IMAGE}_$*:devel -o $@

# DOCKER BASH (debug)
targets = $(addprefix bash_, $(DISTROS))
.PHONY: $(targets)
$(targets): bash_%: cache/%/docker_devel.tar
	${DOCKER_DEVEL_CMD} ${IMAGE}_$*:devel /bin/sh

# CONFIGURE
targets = $(addprefix configure_, $(DISTROS))
.PHONY: configure $(targets)
configure: $(targets)
$(targets): configure_%: cache/%/configure.log
cache/%/configure.log: cache/%/docker_devel.tar \
	../CMakeLists.txt ../*/CMakeLists.txt \
	../cmake/*.CMakeLists.txt ../cmake/*Config.cmake.in
	@docker load -i $<
	${DOCKER_DEVEL_CMD} ${IMAGE}_$*:devel /bin/sh -c \
		"cmake -version && cmake -H. -Bci/cache/$*/build"
	@date > $@

# BUILD
targets = $(addprefix build_, $(DISTROS))
.PHONY: build $(targets)
build: $(targets)
$(targets): build_%: cache/%/build.log
cache/%/build.log: cache/%/configure.log ../Foo ../FooApp
	${DOCKER_DEVEL_CMD} ${IMAGE}_$*:devel /bin/sh -c \
		"cmake --build ci/cache/$*/build --target all"
	@date > $@

# TEST
targets = $(addprefix test_, $(DISTROS))
.PHONY: test $(targets)
test: $(targets)
$(targets): test_%: cache/%/test.log
cache/%/test.log: cache/%/build.log
	${DOCKER_DEVEL_CMD} ${IMAGE}_$*:devel /bin/sh -c \
		"cmake --build ci/cache/$*/build --target test -- CTEST_OUTPUT_ON_FAILURE=1"
	@date > $@

# INSTALL
targets = $(addprefix install_, $(DISTROS))
.PHONY: install $(targets)
install: $(targets)
$(targets): install_%: cache/%/install.log
cache/%/install.log: docker/%/InstallDockerfile cache/%/build.log
	${DOCKER_DEVEL_CMD} ${IMAGE}_$*:devel /bin/sh -c \
		"cmake --build ci/cache/$*/build --target install -- DESTDIR=../install"
	@docker image rm -f ${IMAGE}_$*:install 2>/dev/null
	@rm -f cache/$*/docker_install.tar
	${DOCKER_BUILD_CMD} -t ${IMAGE}_$*:install -f $< cache/$*
	docker save ${IMAGE}_$*:install -o cache/$*/docker_install.tar
	@date > $@

# DOCKER BASH INSTALL (debug)
targets = $(addprefix bash_install_, $(DISTROS))
.PHONY: $(targets)
$(targets): bash_install_%: cache/%/install.log
	@docker load -i cache/$*/docker_install.tar
	${DOCKER_INSTALL_CMD} ${IMAGE}_$*:install /bin/sh

# TEST INSTALL of ProjectConfigs.cmake
targets = $(addprefix test_install_, $(DISTROS))
.PHONY: test_install $(targets)
test_install: $(targets)
$(targets): test_install_%: cache/%/test_install.log
cache/%/test_install.log: cache/%/install.log sample
	@docker load -i cache/$*/docker_install.tar
	${DOCKER_INSTALL_CMD} ${IMAGE}_$*:install /bin/sh -c \
		"cmake -H. -B/cache; \
		cmake --build /cache; \
		cmake --build /cache --target test; \
		cmake --build /cache --target install"
	@date > $@

# CLEAN
targets = $(addprefix clean_, $(DISTROS))
.PHONY: clean $(targets)
clean: $(targets)
$(targets): clean_%:
	-rm -f cache/$*/test_install.log
	-rm -f cache/$*/install.log
	-rm -f cache/$*/test.log
	-rm -f cache/$*/build.log
	-rm -f cache/$*/configure.log
	-rm -rf cache/$*/build

# DISTCLEAN
targets = $(addprefix distclean_, $(DISTROS))
.PHONY: distclean $(targets)
distclean: $(targets)
	docker image prune -f
	rmdir cache
$(targets): distclean_%: clean_%
	-docker image rm -f ${IMAGE}_$*:install 2>/dev/null
	-rm -f cache/$*/docker_install.tar
	-docker image rm -f ${IMAGE}_$*:devel 2>/dev/null
	-rm -f cache/$*/docker_devel.tar
	-rmdir cache/$*
