/* -----------------------------------------------------------------------------
 * Copyright (C) 2013 ARM Limited. All rights reserved.
 *  
 * $Date:        27. June 2013
 * $Revision:    V1.00
 *  
 * Project:      RTE Device Configuration for Freescale Kinetis K20
 * -------------------------------------------------------------------------- */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H


#define GPIO_PORT(num) \
 ((num == 0) ? PORTA : \
  (num == 1) ? PORTB : \
  (num == 2) ? PORTC : \
  (num == 3) ? PORTD : \
  (num == 4) ? PORTE : \
  NULL)


// <h> Clock Configuration
//   <o> System Clock <1-999999999>
#define RTE_SYSCLK                      48000000
//   <o> Bus Clock    <1-999999999>
#define RTE_BUSCLK                      48000000
// </h>


// <e> UART0 (Universal asynchronous receiver transmitter)
#define RTE_UART0                      0

//   <o> UART0_TX Pin <0=>PTA2 <1=>PTB17 <2=>PTD7
#define RTE_UART0_TX_ID                0
#if    (RTE_UART0_TX_ID == 0)
#define RTE_UART0_TX_PORT              PORTA
#define RTE_UART0_TX_BIT               2
#define RTE_UART0_TX_AF                GPIO_AF_ALT2
#elif  (RTE_UART0_TX_ID == 1)
#define RTE_UART0_TX_PORT              PORTB
#define RTE_UART0_TX_BIT               17
#define RTE_UART0_TX_AF                GPIO_AF_ALT3
#elif  (RTE_UART0_TX_ID == 2)
#define RTE_UART0_TX_PORT              PORTD
#define RTE_UART0_TX_BIT               7
#define RTE_UART0_TX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART0_TX Pin Configuration!"
#endif

//   <o> UART0_RX Pin <0=>PTA1 <1=>PTB16 <2=>PTD6
#define RTE_UART0_RX_ID                0
#if    (RTE_UART0_RX_ID == 0)
#define RTE_UART0_RX_PORT              PORTA
#define RTE_UART0_RX_BIT               1
#define RTE_UART0_RX_AF                GPIO_AF_ALT2
#elif  (RTE_UART0_RX_ID == 1)
#define RTE_UART0_RX_PORT              PORTB
#define RTE_UART0_RX_BIT               16
#define RTE_UART0_RX_AF                GPIO_AF_ALT3
#elif  (RTE_UART0_RX_ID == 2)
#define RTE_UART0_RX_PORT              PORTD
#define RTE_UART0_RX_BIT               6
#define RTE_UART0_RX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART0_RX Pin Configuration!"
#endif

//     <e> Hardware flow control
//       <o1> UART0_CTS Pin <0=>PTA0 <1=>PTB3 <2=>PTD5
//       <o2> UART0_RTS Pin <0=>PTA3 <1=>PTB2 <2=>PTD4
//       <o3.0> Manual CTS/RTS
//     </e>
#define RTE_UART0_HW_FLOW              0
#define RTE_UART0_CTS_ID               0
#define RTE_UART0_RTS_ID               0
#define RTE_UART0_MANUAL_FLOW          0
#if    (RTE_UART0_CTS_ID == 0)
#define RTE_UART0_CTS_PORT             PORTA
#define RTE_UART0_CTS_BIT              0
#define RTE_UART0_CTS_AF               GPIO_AF_ALT2
#elif  (RTE_UART0_CTS_ID == 1)
#define RTE_UART0_CTS_PORT             PORTB
#define RTE_UART0_CTS_BIT              2
#define RTE_UART0_CTS_AF               GPIO_AF_ALT3
#elif  (RTE_UART0_CTS_ID == 2)
#define RTE_UART0_CTS_PORT             PORTD
#define RTE_UART0_CTS_BIT              5
#define RTE_UART0_CTS_AF               GPIO_AF_ALT3
#else
#error "Invalid UART0_CTS Pin Configuration!"
#endif
#if    (RTE_UART0_RTS_ID == 0)
#define RTE_UART0_RTS_PORT             PORTA
#define RTE_UART0_RTS_BIT              3
#define RTE_UART0_RTS_AF               GPIO_AF_ALT2
#elif  (RTE_UART0_RTS_ID == 1)
#define RTE_UART0_RTS_PORT             PORTB
#define RTE_UART0_RTS_BIT              2
#define RTE_UART0_RTS_AF               GPIO_AF_ALT3
#elif  (RTE_UART0_RTS_ID == 2)
#define RTE_UART0_RTS_PORT             PORTD
#define RTE_UART0_RTS_BIT              4
#define RTE_UART0_RTS_AF               GPIO_AF_ALT3
#else
#error "Invalid UART0_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <0=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART0_RX_DMA               0
#define RTE_UART0_RX_DMA_CHANNEL       0
#define RTE_UART0_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <0=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART0_TX_DMA               0
#define RTE_UART0_TX_DMA_CHANNEL       1
#define RTE_UART0_TX_DMA_PRIORITY      0

// </e>


// <e> UART1 (Universal asynchronous receiver transmitter)
#define RTE_UART1                      1

//   <o> UART1_TX Pin <0=>PTE0 <1=>PTC4 
#define RTE_UART1_TX_ID                1
#if    (RTE_UART1_TX_ID == 0)
#define RTE_UART1_TX_PORT              PORTE
#define RTE_UART1_TX_BIT               0
#define RTE_UART1_TX_AF                GPIO_AF_ALT3
#elif  (RTE_UART1_TX_ID == 1)
#define RTE_UART1_TX_PORT              PORTC
#define RTE_UART1_TX_BIT               4
#define RTE_UART1_TX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART1_TX Pin Configuration!"
#endif

//   <o> UART1_RX Pin <0=>PTE1 <1=>PTC3
#define RTE_UART1_RX_ID                1
#if    (RTE_UART1_RX_ID == 0)
#define RTE_UART1_RX_PORT              PORTE
#define RTE_UART1_RX_BIT               1
#define RTE_UART1_RX_AF                GPIO_AF_ALT3
#elif  (RTE_UART1_RX_ID == 1)
#define RTE_UART1_RX_PORT              PORTC
#define RTE_UART1_RX_BIT               3
#define RTE_UART1_RX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART1_RX Pin Configuration!"
#endif


//     <e> Hardware flow control
//       <o1> UART1_CTS Pin <0=>PTC2
//       <o2> UART1_RTS Pin <0=>PTC1
//       <o3.0> Manual CTS/RTS
//     </e>
#define RTE_UART1_HW_FLOW              0
#define RTE_UART1_CTS_ID               0
#define RTE_UART1_RTS_ID               0
#define RTE_UART1_MANUAL_FLOW          0
#if    (RTE_UART1_CTS_ID == 0)
#define RTE_UART1_CTS_PORT             PORTC
#define RTE_UART1_CTS_BIT              2
#define RTE_UART1_CTS_AF               GPIO_AF_ALT3
#else
#error "Invalid UART1_CTS Pin Configuration!"
#endif
#if    (RTE_UART1_RTS_ID == 0)
#define RTE_UART1_RTS_PORT             PORTC
#define RTE_UART1_RTS_BIT              1
#define RTE_UART1_RTS_AF               GPIO_AF_ALT3
#else
#error "Invalid UART1_RTS Pin Configuration!"
#endif

//   <e> DMA Rx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART1_RX_DMA               0
#define RTE_UART1_RX_DMA_CHANNEL       0
#define RTE_UART1_RX_DMA_PRIORITY      0


//   <e> DMA Tx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART1_TX_DMA               0
#define RTE_UART1_TX_DMA_CHANNEL       0
#define RTE_UART1_TX_DMA_PRIORITY      0

// </e>


// <e> UART2 (Universal asynchronous receiver transmitter)
#define RTE_UART2                      0

//   <o> UART2_TX Pin <0=>PTD3
#define RTE_UART2_TX_ID                0
#if    (RTE_UART2_TX_ID == 0)
#define RTE_UART2_TX_PORT              PORTD
#define RTE_UART2_TX_BIT               3
#define RTE_UART2_TX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART2_TX Pin Configuration!"
#endif

//   <o> UART2_RX Pin <0=>PTD2 
#define RTE_UART2_RX_ID                0
#if    (RTE_UART2_RX_ID == 0)
#define RTE_UART2_RX_PORT              PORTD
#define RTE_UART2_RX_BIT               2
#define RTE_UART2_RX_AF                GPIO_AF_ALT3
#else
#error "Invalid UART2_RX Pin Configuration!"
#endif


//     <e> Hardware flow control
//       <o1> UART2_CTS Pin <0=>PTD1
//       <o2> UART2_RTS Pin <0=>PTD0
//       <o3.0> Manual CTS/RTS
//     </e>
#define RTE_UART2_HW_FLOW              0
#define RTE_UART2_CTS_ID               0
#define RTE_UART2_RTS_ID               0
#define RTE_UART2_MANUAL_FLOW          0
#if    (RTE_UART2_CTS_ID == 0)
#define RTE_UART2_CTS_PORT             PORTD
#define RTE_UART2_CTS_BIT              1
#define RTE_UART2_CTS_AF                GPIO_AF_ALT3
#else
#error "Invalid UART2_CTS Pin Configuration!"
#endif
#if    (RTE_UART2_RTS_ID == 0)
#define RTE_UART2_RTS_PORT             PORTD
#define RTE_UART2_RTS_BIT              0
#define RTE_UART2_RTS_AF               GPIO_AF_ALT3
#else
#error "Invalid UART2_RTS Pin Configuration!"
#endif


//   <e> DMA Rx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART2_RX_DMA               0
#define RTE_UART2_RX_DMA_CHANNEL       0
#define RTE_UART2_RX_DMA_PRIORITY      0

//   <e> DMA Tx
//     <o1> Channel <0=>0 <1=>1 <2=>2 <3=>3 
//     <i>  Selects DMA Channel (0..15)
//     <o2> Priority <0=>Lowest <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7 <8=>8 <9=>9 <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>Highest
//     <i>  Selects DMA Priority
//   </e>
#define RTE_UART2_TX_DMA               0
#define RTE_UART2_TX_DMA_CHANNEL       3
#define RTE_UART2_TX_DMA_PRIORITY      0

// </e>


// <e> USB0 Controller
#define RTE_USB_USB0                    1

//     <h> Endpoints
//     <i> Reduce memory requirements of Driver by disabling unused endpoints
//       <o0.1> Endpoint 1
//       <o0.2> Endpoint 2
//       <o0.3> Endpoint 3
//       <o0.4> Endpoint 4
//       <o0.5> Endpoint 5
//       <o0.6> Endpoint 6
//       <o0.7> Endpoint 7
//       <o0.8> Endpoint 8
//       <o0.9> Endpoint 9
//       <o0.10> Endpoint 10
//       <o0.11> Endpoint 11
//       <o0.12> Endpoint 12
//       <o0.13> Endpoint 13
//       <o0.14> Endpoint 14
//       <o0.15> Endpoint 15
//     </h>
#define RTE_USB_USB0_DEV_EP             0x0000003F

// </e>

#endif  /* __RTE_DEVICE_H */

