#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_MITIGATION_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x14\x00\x00\x00\xcc\x25\xd2\xe5"
	"pci_iounmap\0"
	"\x1c\x00\x00\x00\x21\x1f\xd7\xf9"
	"pci_release_region\0\0"
	"\x1c\x00\x00\x00\x0c\xa9\x59\x26"
	"pci_disable_device\0\0"
	"\x20\x00\x00\x00\x49\x1a\x8f\x46"
	"pci_unregister_driver\0\0\0"
	"\x1c\x00\x00\x00\xb8\xc7\x17\xfb"
	"pci_enable_device\0\0\0"
	"\x1c\x00\x00\x00\x1f\x9c\x79\x45"
	"pci_request_region\0\0"
	"\x14\x00\x00\x00\xcc\x4f\x26\x8f"
	"pci_iomap\0\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x20\x00\x00\x00\x1f\x5c\x90\xf0"
	"__pci_register_driver\0\0\0"
	"\x18\x00\x00\x00\xde\x9f\x8a\x25"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");

MODULE_ALIAS("pci:v00008086d0000100Esv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "F84BD7D983AED27245CAAFC");
