#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/mod_devicetable.h>
#include <linux/io.h>

#define DRV_NAME "pci_eth"

// Supported PCI device ID table
static const struct pci_device_id pci_eth_ids[] = {
    { PCI_DEVICE(0x8086, 0x100E) }, // Intel 82540EM Gigabit Ethernet Controller
    { 0, }
};
MODULE_DEVICE_TABLE(pci, pci_eth_ids);

// Probe function — called when a matching device is found
static int pci_eth_probe(struct pci_dev *pdev, const struct pci_device_id *ent) {
    int ret;
    void __iomem *mmio_base;
    resource_size_t bar_start, bar_len;

    printk(KERN_INFO DRV_NAME ": Probing device [vendor=0x%x, device=0x%x]\n",
           pdev->vendor, pdev->device);

    // Enable the device
    ret = pci_enable_device(pdev);
    if (ret) {
        printk(KERN_ERR DRV_NAME ": Failed to enable PCI device\n");
        return ret;
    }

    // Request BAR0 region
    ret = pci_request_region(pdev, 0, DRV_NAME);
    if (ret) {
        printk(KERN_ERR DRV_NAME ": Failed to request BAR0\n");
        pci_disable_device(pdev);
        return ret;
    }

    // Map BAR0
    mmio_base = pci_iomap(pdev, 0, 0);
    if (!mmio_base) {
        printk(KERN_ERR DRV_NAME ": Failed to iomap BAR0\n");
        pci_release_region(pdev, 0);
        pci_disable_device(pdev);
        return -ENOMEM;
    }

    // Debug: Print BAR0 details
    bar_start = pci_resource_start(pdev, 0);
    bar_len = pci_resource_len(pdev, 0);
    printk(KERN_INFO DRV_NAME ": BAR0 mapped at %p, physical start=0x%llx, len=%llu\n",
           mmio_base, (unsigned long long)bar_start, (unsigned long long)bar_len);

    // Save for use in remove()
    pci_set_drvdata(pdev, mmio_base);

    return 0;
}

// Remove function — called when driver is unloaded or device removed
static void pci_eth_remove(struct pci_dev *pdev) {
    void __iomem *mmio_base = pci_get_drvdata(pdev);

    pci_iounmap(pdev, mmio_base);
    pci_release_region(pdev, 0);
    pci_disable_device(pdev);

    printk(KERN_INFO DRV_NAME ": Device removed and cleaned up\n");
}

// PCI driver registration
static struct pci_driver pci_eth_driver = {
    .name = DRV_NAME,
    .id_table = pci_eth_ids,
    .probe = pci_eth_probe,
    .remove = pci_eth_remove,
};

// Module init
static int __init pci_eth_init(void) {
    printk(KERN_INFO DRV_NAME ": Loading PCI Ethernet driver\n");
    return pci_register_driver(&pci_eth_driver);
}

// Module exit
static void __exit pci_eth_exit(void) {
    printk(KERN_INFO DRV_NAME ": Unloading PCI Ethernet driver\n");
    pci_unregister_driver(&pci_eth_driver);
}

module_init(pci_eth_init);
module_exit(pci_eth_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A minimal PCI Ethernet driver");
MODULE_VERSION("1.0");
