/****************************************************************************
 * include/nuttx/virtio/virtio-mmio.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_VIRTIO_VIRTIO_MMIO_H
#define __INCLUDE_NUTTX_VIRTIO_VIRTIO_MMIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stddef.h>
#include <stdint.h>

#ifdef CONFIG_DRIVERS_VIRTIO_MMIO

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: virtio_register_mmio_device
 *
 * Description:
 *   Register virtio mmio device to the virtio bus
 *
 ****************************************************************************/

int virtio_register_mmio_device(FAR void *regs, int irq);

/****************************************************************************
 * Name: virtio_register_mmio_device_secure
 *
 * Description:
 *   Register secure virtio mmio device to the virtio bus
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_TRUSTZONE_SECURE
int virtio_register_mmio_device_secure(FAR void *regs, int irq);
#endif

/****************************************************************************
 * Name: virtio_mmio_pool_create
 *
 * Description:
 *   Create a pool from the memory region a virtio mmio device is restricted
 *   to, e.g. the only one a hypervisor shares with the virtual machine that
 *   implements the device. The address and the size of the region must be
 *   multiples of CONFIG_DRIVERS_VIRTIO_MMIO_POOL_BLOCKSIZE.
 *
 * Returned Value:
 *   The pool, to be passed to virtio_register_mmio_device_pool() for each
 *   device that shares the region, or NULL on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_DRIVERS_VIRTIO_MMIO_POOL
struct virtio_mmio_pool_s;

FAR struct virtio_mmio_pool_s *virtio_mmio_pool_create(FAR void *base,
                                                       size_t size);

/****************************************************************************
 * Name: virtio_register_mmio_device_pool
 *
 * Description:
 *   Register to the virtio bus a virtio mmio device that can only access
 *   the memory of a pool. Its virtqueues and the buffers its driver
 *   allocates come from the pool, and the other buffers the driver hands
 *   to the device are bounced through it.
 *
 ****************************************************************************/

int virtio_register_mmio_device_pool(FAR void *regs, int irq,
                                     FAR struct virtio_mmio_pool_s *pool);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_DRIVERS_VIRTIO_MMIO */
#endif /* __INCLUDE_NUTTX_VIRTIO_VIRTIO_MMIO_H */
