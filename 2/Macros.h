/*
 * Macros.h
 *
 *  Created on: Aug 18, 2019
 *      Author: abdul
 */

#ifndef MACROS_H_
#define MACROS_H_

#define SetBit(REG,BIT)		(REG |= (1<<BIT))
#define ClrBit(REG,BIT)		(REG &=~(1<<BIT))
#define TglBit(REG,BIT)		(REG ^= (1<<BIT))
#define GetBit(REG,BIT)		(REG & (1<<BIT))


#endif /* MACROS_H_ */
