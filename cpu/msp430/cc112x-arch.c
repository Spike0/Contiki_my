/**
 * \addtogroup cc112x
 * @{
 *
 * \file
 * CC112X MSP430 dependent code
 *
 * \author Martin Chaplet <m.chaplet@kerlink.fr>
 */

/*
 * Copyright (c) 2012, Kerlink
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 * Greatly inspired from cc2420-arch
 *
 * $Id: $
 */

#include "contiki.h"
#include "contiki-net.h"

#include "dev/spi.h"
#include "dev/cc112x.h"
#include "isr_compat.h"

/*---------------------------------------------------------------------------*/
ISR(CC112X_IRQ, cc112x_port1_interrupt)
{
  ENERGEST_ON(ENERGEST_TYPE_IRQ);

  if(cc112x_interrupt()) {
    LPM4_EXIT;
  }

  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}

/*---------------------------------------------------------------------------*/
void
cc112x_arch_init(void)
{
  spi_init();

  /* all input by default, set these as output */
  CC112X_CSN_PORT(DIR) |= BV(CC112X_CSN_PIN);
  CC112X_RESET_PORT(DIR) |= BV(CC112X_RESET_PIN);

  CC112X_SPI_DISABLE();                /* Unselect radio. */
}
/*---------------------------------------------------------------------------*/
