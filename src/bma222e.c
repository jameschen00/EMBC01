/**
 ** ############################################################################
 **
 ** @file  bma222e.c
 ** @brief driver implementation for an i2c-based BMA222E accelerometer
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 **
 ** ############################################################################
 ** EM Microelectronic-US Inc. License Agreement
 **
 ** Please read this License Agreement ("Agreement") carefully before
 ** accessing, copying, using, incorporating, modifying or in any way providing
 ** ("Using" or "Use") this source code.  By Using this source code, you: (i)
 ** warrant and represent that you have obtained all authorizations and other
 ** applicable consents required empowering you to enter into and (ii) agree to
 ** be bound by the terms of this Agreement.  If you do not agree to this
 ** Agreement, then you are not permitted to Use this source code, in whole or
 ** in part.
 **
 ** Pursuant to the terms in the accompanying software license agreement and
 ** Terms of Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html
 ** (the terms of each are incorporated herein by this reference) and subject to
 ** the disclaimer and limitation of liability set forth below, EM
 ** Microelectronic US Inc. ("EM"), grants strictly to you, without the right to
 ** sublicense, a non-exclusive, non-transferable, revocable, worldwide license
 ** to use the source code to modify the software program for the sole purpose
 ** of developing object and executable versions that execute solely and
 ** exclusively on devices manufactured by or for EM or your products that use
 ** or incorporate devices manufactured by or for EM; provided that, you clearly
 ** notify third parties regarding the source of such modifications or Use.
 **
 ** Without limiting any of the foregoing, the name "EM Microelectronic-US
 ** Inc." or that of any of the EM Parties (as such term is defined below) must
 ** not be Used to endorse or promote products derived from the source code
 ** without prior written permission from an authorized representative of EM
 ** Microelectronic US Inc.
 **
 ** THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT ANY
 ** SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 ** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 ** PURPOSE ARE DISCLAIMED.  ALSO, THERE IS NO WARRANTY OF NON-INFRINGEMENT,
 ** TITLE OR QUIET ENJOYMENT.
 **
 ** IN NO EVENT SHALL EM MICROELECTRONIC US INC., ITS AFFILIATES, PARENT AND
 ** ITS/THEIR RESPECTIVE LICENSORS, THIRD PARTY PROVIDERS, REPRESENTATIVES,
 ** AGENTS AND ASSIGNS ("COLLECTIVLEY, "EM PARTIES") BE LIABLE FOR ANY DIRECT,
 ** INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, EXEMPLARY, OR CONSEQUENTIAL
 ** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 ** SERVICES; LOSS OF USE, DATA, EQUIPMENT, SYSTEMS, SOFTWARE, TECHNOLOGY,
 ** SERVICES, GOODS, CONTENT, MATERIALS OR PROFITS; BUSINESS INTERRUPTION OR
 ** OTHER ECONOMIC LOSS OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
 ** LIMITED TO ANY DEFENSE THEREOF) HOWEVER CAUSED AND ON ANY THEORY OF
 ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE
 ** CODE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  NOTWITHSTANDING
 ** ANYTHING ELSE TO THE CONTRARY, IN NO EVENT WILL THE EM PARTIES' AGGREGATE
 ** LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF YOUR USE OF THE SOURCE
 ** CODE EXCEED ONE HUNDRED U.S. DOLLARS (U.S. $100).
 **
 ** Please refer to the accompanying software license agreement and Terms of
 ** Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html to better
 ** understand all of your rights and obligations hereunder.
 ** ############################################################################
 */

#include "Types.h"
#include "irqmsk.h"
#include "ports.h"

#include "config.h"
#include "i2cmaster.h"
#include "bma222e.h"

/**
 * @brief BMA222E registers.
 */
#define BMA222E_REG_BGW_CHIPID    (0x00)
#define BMA222E_REG_ACCD_X_LSB    (0x02)
#define BMA222E_REG_ACCD_X_MSB    (0x03)
#define BMA222E_REG_ACCD_Y_LSB    (0x04)
#define BMA222E_REG_ACCD_Y_MSB    (0x05)
#define BMA222E_REG_ACCD_Z_LSB    (0x06)
#define BMA222E_REG_ACCD_Z_MSB    (0x07)
#define BMA222E_REG_ACCD_TEMP     (0x08)
#define BMA222E_REG_INT_STATUS_0  (0x09)
#define BMA222E_REG_INT_STATUS_1  (0x0A)
#define BMA222E_REG_INT_STATUS_2  (0x0B)
#define BMA222E_REG_INT_STATUS_3  (0x0C)
#define BMA222E_REG_FIFO_STATUS   (0x0E)
#define BMA222E_REG_PMU_RANGE     (0x0F)
#define BMA222E_REG_PMU_BW        (0x10)
#define BMA222E_REG_PMU_LPW       (0x11)
#define BMA222E_REG_PMU_LOW_NOISE (0x12)
#define BMA222E_REG_ACCD_HBW      (0x13)
#define BMA222E_REG_BGW_SOFTRESET (0x14)
#define BMA222E_REG_INT_EN_0      (0x16)
#define BMA222E_REG_INT_EN_1      (0x17)
#define BMA222E_REG_INT_EN_2      (0x18)
#define BMA222E_REG_INT_MAP_0     (0x19)
#define BMA222E_REG_INT_MAP_1     (0x1A)
#define BMA222E_REG_INT_MAP_2     (0x1B)
#define BMA222E_REG_INT_SRC       (0x1E)
#define BMA222E_REG_INT_OUT_CTRL  (0x20)
#define BMA222E_REG_INT_RST_LATCH (0x21)
#define BMA222E_REG_INT_0         (0x22)
#define BMA222E_REG_INT_1         (0x23)
#define BMA222E_REG_INT_2         (0x24)
#define BMA222E_REG_INT_3         (0x25)
#define BMA222E_REG_INT_4         (0x26)
#define BMA222E_REG_INT_5         (0x27)
#define BMA222E_REG_INT_6         (0x28)
#define BMA222E_REG_INT_7         (0x29)
#define BMA222E_REG_INT_8         (0x2A)
#define BMA222E_REG_INT_9         (0x2B)
#define BMA222E_REG_INT_A         (0x2C)
#define BMA222E_REG_INT_B         (0x2D)
#define BMA222E_REG_INT_C         (0x2E)
#define BMA222E_REG_INT_D         (0x2F)
#define BMA222E_REG_FIFO_CONFIG_0 (0x30)
#define BMA222E_REG_PMU_SELF_TEST (0x32)
#define BMA222E_REG_TRIM_NVM_CTRL (0x33)
#define BMA222E_REG_BGW_SPI3_WDT  (0x34)
#define BMA222E_REG_OFC_CTRL      (0x36)
#define BMA222E_REG_OFC_SETTING   (0x37)
#define BMA222E_REG_OFC_OFFSET_X  (0x38)
#define BMA222E_REG_OFC_OFFSET_Y  (0x39)
#define BMA222E_REG_OFC_OFFSET_Z  (0x3A)
#define BMA222E_REG_TRIM_GP0      (0x3B)
#define BMA222E_REG_TRIM_GP1      (0x3C)
#define BMA222E_REG_FIFO_CONFIG_1 (0x3E)
#define BMA222E_REG_FIFO_DATA     (0x3F)

/**
 * @brief Options for the PMU_RANGE register.
 */
#define BMA222E_PMU_RANGE_2G            (0x03)
#define BMA222E_PMU_RANGE_4G            (0x05)
#define BMA222E_PMU_RANGE_8G            (0x08)
#define BMA222E_PMU_RANGE_16G           (0x0C)

/**
 * @brief Options for the PMU_LPW register.
 */
#define BMA222E_PMU_LPW_SUSPEND         (0x80)
#define BMA222E_PMU_LPW_LOWPOWER_EN     (0x40)
#define BMA222E_PMU_LPW_DEEP_SUSPEND    (0x20)
#define BMA222E_PMU_LPW_SLEEP_DUR_0_5MS (0x00)
#define BMA222E_PMU_LPW_SLEEP_DUR_1MS   (0x0C)
#define BMA222E_PMU_LPW_SLEEP_DUR_2MS   (0x0E)
#define BMA222E_PMU_LPW_SLEEP_DUR_4MS   (0x10)
#define BMA222E_PMU_LPW_SLEEP_DUR_6MS   (0x12)
#define BMA222E_PMU_LPW_SLEEP_DUR_10MS  (0x14)
#define BMA222E_PMU_LPW_SLEEP_DUR_25MS  (0x16)
#define BMA222E_PMU_LPW_SLEEP_DUR_50MS  (0x18)
#define BMA222E_PMU_LPW_SLEEP_DUR_100MS (0x1A)
#define BMA222E_PMU_LPW_SLEEP_DUR_500MS (0x1C)
#define BMA222E_PMU_LPW_SLEEP_DUR_1S    (0x1E)

/**
 * @brief Options for the INT_MAP_0 register.
 */
#define BMA222E_INT_MAP_INT1_FLAT       (0x80)
#define BMA222E_INT_MAP_INT1_ORIENT     (0x40)
#define BMA222E_INT_MAP_INT1_S_TAP      (0x20)
#define BMA222E_INT_MAP_INT1_D_TAP      (0x10)
#define BMA222E_INT_MAP_INT1_SLO_NO_MOT (0x08)
#define BMA222E_INT_MAP_INT1_SLOPE      (0x04)
#define BMA222E_INT_MAP_INT1_HIGH       (0x02)
#define BMA222E_INT_MAP_INT1_LOW        (0x01)

/**
 * @brief Options for the INT_EN_0 register.
 */
#define BMA222E_INT_EN_FLAT_EN          (0x80)
#define BMA222E_INT_EN_ORIENT_EN        (0x40)
#define BMA222E_INT_EN_S_TAP_EN         (0x20)
#define BMA222E_INT_EN_D_TAP_EN         (0x10)
#define BMA222E_INT_EN_RESERVED         (0x08)
#define BMA222E_INT_EN_SLOPE_EN_Z       (0x04)
#define BMA222E_INT_EN_SLOPE_EN_Y       (0x02)
#define BMA222E_INT_EN_SLOPE_EN_X       (0x01)

/**
 * @brief Options for the INT_EN_1 register.
 */
#define BMA222E_INT_EN_RESERVED2        (0x80)
#define BMA222E_INT_EN_FWM_EN           (0x40)
#define BMA222E_INT_EN_FFULL_EN         (0x20)
#define BMA222E_INT_EN_DATA_EN          (0x10)
#define BMA222E_INT_EN_LOW_EN           (0x08)
#define BMA222E_INT_EN_HIGH_EN_Z        (0x04)
#define BMA222E_INT_EN_HIGH_EN_Y        (0x02)
#define BMA222E_INT_EN_HIGH_EN_X        (0x01)

/**
 * @brief Options for the INT_OUT_CTRL register.
 */
#define BMA222E_INT_OUT_CTRL_INT2_OD    (0x08)
#define BMA222E_INT_OUT_CTRL_INT2_LVL   (0x04)
#define BMA222E_INT_OUT_CTRL_INT1_OD    (0x02)
#define BMA222E_INT_OUT_CTRL_INT1_LVL   (0x01)

/**
 * @brief Options for the INT_RST_LATCH register.
 */
#define BMA222E_INT_RST_LATCH_NONE      (0x00)
#define BMA222E_INT_RST_LATCH_250MS     (0x01)
#define BMA222E_INT_RST_LATCH_500MS     (0x02)
#define BMA222E_INT_RST_LATCH_1S        (0x03)
#define BMA222E_INT_RST_LATCH_2S        (0x04)
#define BMA222E_INT_RST_LATCH_4S        (0x05)
#define BMA222E_INT_RST_LATCH_8S        (0x06)
#define BMA222E_INT_RST_LATCH_LATCHED   (0x07)
#define BMA222E_INT_RST_LATCH_NONE2     (0x08)
#define BMA222E_INT_RST_LATCH_250US     (0x09)
#define BMA222E_INT_RST_LATCH_500US     (0x0A)
#define BMA222E_INT_RST_LATCH_1MS       (0x0B)
#define BMA222E_INT_RST_LATCH_12_5MS    (0x0C)
#define BMA222E_INT_RST_LATCH_25MS      (0x0D)
#define BMA222E_INT_RST_LATCH_50MS      (0x0E)
#define BMA222E_INT_RST_LATCH_LATCHED2  (0x0F)
#define BMA222E_INT_RST_LATCH_RESET_INT (0x80)

/**
 * @brief Options for the INT_0 Low-g delay time register.
 * Delay (ms) = (val + 1) * 2
 * Default if unset is 20ms
 */
#define BMA222E_INT_0_LOW_DUR(val)       (val)

/**
 * @brief Options for the INT_1 Low-g threshold register.
 * LSB = 7.81 mg, full range = 0 .. 1.992 g
 * Default if unset is 375 mg
 */
#define BMA222E_INT_1_LOW_TH(val)       (val)

/**
 * @brief Options for the INT_2 register.
 */
#define BMA222E_INT_2_LOW_HY_0G         (0x00)
#define BMA222E_INT_2_LOW_HY_125MG      (0x01)
#define BMA222E_INT_2_LOW_HY_250MG      (0x02)
#define BMA222E_INT_2_LOW_HY_375MG      (0x03)
#define BMA222E_INT_2_LOW_G_SUM_MODE    (0x04)

/**
 * @brief Options for the INT_5 register.
 */
#define BMA222E_INT_5_SLOPE_DUR(val)    (((val)-1) & 0x03)

/**
 * @brief Options for the INT_6 register.
 */
#define BMA222E_INT_6_SLOPE_TH(val)     (val)

/**
 * @brief Options for the INT_8 register.
 */
#define BMA222E_INT_8_TAP_QUIET_30MS    (0x00)
#define BMA222E_INT_8_TAP_QUIET_20MS    (0x80)
#define BMA222E_INT_8_TAP_SHOCK_50MS    (0x00)
#define BMA222E_INT_8_TAP_SHOCK_75MS    (0x80)
#define BMA222E_INT_8_TAP_DUR_50MS      (0x00)
#define BMA222E_INT_8_TAP_DUR_100MS     (0x01)
#define BMA222E_INT_8_TAP_DUR_150MS     (0x02)
#define BMA222E_INT_8_TAP_DUR_200MS     (0x03)
#define BMA222E_INT_8_TAP_DUR_250MS     (0x04)
#define BMA222E_INT_8_TAP_DUR_375MS     (0x05)
#define BMA222E_INT_8_TAP_DUR_500MS     (0x06)
#define BMA222E_INT_8_TAP_DUR_700MS     (0x07)

/**
 * @brief Options for the INT_9 register.
 */
#define BMA222E_INT_9_TAP_SAMP_2        (0x00)
#define BMA222E_INT_9_TAP_SAMP_4        (0x40)
#define BMA222E_INT_9_TAP_SAMP_8        (0x80)
#define BMA222E_INT_9_TAP_SAMP_16       (0xC0)
#define BMA222E_INT_9_TAP_TH(val)       ((val) & 0x1F)

/**
 * @brief I2C slave address of the BMA222E.
 */
#define BMA222E_SLAVE_ADDR              (0x18)

/**
 * @brief Expected Chip ID (read from the BGW_CHIPID register).
 */
#define BMA222E_CHIPID                 (0xF8)
#define BMA250_CHIPID                  (0x03)


/**
 *******************************************************************************
 * @brief Intial setup of the BMA222E chip at power on
 *
 * @param  none
 * @return success: true if initialization completed successfully
 *******************************************************************************
 */
UINT8 BMA222E_PowerOnInit(void)
{
   Dis_IRQ_Port1();    // Halt events

   // Validate the chip ID
   UINT8 chipID = fI2cGetData(BMA222E_SLAVE_ADDR, BMA222E_REG_BGW_CHIPID);

   if(chipID != BMA222E_CHIPID && chipID != BMA222E_CHIPID)
   {
       return 0;
   }

   // INT1: active high, push-pull
   fI2cSendData(BMA222E_INT_OUT_CTRL_INT1_LVL, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_OUT_CTRL);

   // Wake the sensor and place into low power mode.
   fI2cSendData(BMA222E_PMU_LPW_LOWPOWER_EN | BMA222E_PMU_LPW_SLEEP_DUR_4MS, 
                BMA222E_SLAVE_ADDR, BMA222E_REG_PMU_LPW);
   BMA222E_Wake();
   return 1;
}

/**
 *******************************************************************************
 *
 * @brief provide interrupts when any movement is detected.
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_EnterMovementDetectionMode(void)
{

   // Map the slope (any movement) interrupt to INT1.
   fI2cSendData(BMA222E_INT_MAP_INT1_SLOPE,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_MAP_0);

   // Clear interrupts and latch interrupts for 2 seconds.
   fI2cSendData(BMA222E_INT_RST_LATCH_RESET_INT | BMA222E_INT_RST_LATCH_2S,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_RST_LATCH);

    // Low power mode (50ms)
    fI2cSendData(BMA222E_PMU_LPW_LOWPOWER_EN | BMA222E_PMU_LPW_SLEEP_DUR_50MS,
                 BMA222E_SLAVE_ADDR,
                 BMA222E_REG_PMU_LPW);

   // Set the slope threshold to 0.25g (125mg per count at 16G range).
   fI2cSendData(BMA222E_INT_6_SLOPE_TH(2),
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_6);

   // Slope triggers if 2 consecutive slope data points are above slope_th.
   fI2cSendData(BMA222E_INT_5_SLOPE_DUR(2), 
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_5);

   // Slope (any movement) interrupt enable.
   fI2cSendData(BMA222E_INT_EN_SLOPE_EN_X | BMA222E_INT_EN_SLOPE_EN_Y |
                BMA222E_INT_EN_SLOPE_EN_Z, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_0);
}

/**
 *******************************************************************************
 * @brief provide interrupts when "taps" are detected.
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_EnterTapDetectionMode(void)
{

   // Map the single tap interrupt to INT1.
   fI2cSendData(BMA222E_INT_MAP_INT1_S_TAP,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_MAP_0);

    // Low power mode (4ms)
    fI2cSendData(BMA222E_PMU_LPW_LOWPOWER_EN | BMA222E_PMU_LPW_SLEEP_DUR_4MS,
                 BMA222E_SLAVE_ADDR, BMA222E_REG_PMU_LPW);

   // Clear interrupts and latch interrupts for 1ms.
   fI2cSendData(BMA222E_INT_RST_LATCH_RESET_INT | BMA222E_INT_RST_LATCH_1MS,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_RST_LATCH);

   // Tap quiet and shock duration.
   fI2cSendData(BMA222E_INT_8_TAP_QUIET_20MS | BMA222E_INT_8_TAP_SHOCK_50MS,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_8);

   // Tap threshold (a value in the range 0-31).
   // tap_th * 62.5mg (2g-range), 125mg (4g-range), 250mg (8g-range), 500mg (16g-range).
   fI2cSendData(BMA222E_INT_9_TAP_SAMP_2 | BMA222E_INT_9_TAP_TH(4),
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_9);

   // Single tap interrupt enable.
   fI2cSendData(BMA222E_INT_EN_S_TAP_EN,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_0);
}

/**
 *******************************************************************************
 * @brief provide interrupts when "falls" are detected.
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_EnterFallDetectionMode(void)
{

   // Map the low-g (fall) interrupt to INT1.
   fI2cSendData(BMA222E_INT_MAP_INT1_LOW, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_MAP_0);

    // Low power mode (100ms)
    fI2cSendData(BMA222E_PMU_LPW_LOWPOWER_EN | BMA222E_PMU_LPW_SLEEP_DUR_100MS,
                 BMA222E_SLAVE_ADDR, BMA222E_REG_PMU_LPW);

   // Clear interrupts and latch interrupts for 2 seconds.
   fI2cSendData(BMA222E_INT_RST_LATCH_RESET_INT | BMA222E_INT_RST_LATCH_2S,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_RST_LATCH);

   // Set the hysteresis of the low-g interrupt to 0.375g.
   fI2cSendData(BMA222E_INT_2_LOW_G_SUM_MODE | BMA222E_INT_2_LOW_HY_375MG,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_2);

   // Set the low-g threshold to 0.25g.
   fI2cSendData(BMA222E_INT_1_LOW_TH(32), // 32 * 7.81 = 250mg
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_1);

   // Set the low-g event duration
   fI2cSendData(BMA222E_INT_0_LOW_DUR(4), // low duration(ms) = ( X + 1 ) * 2
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_0);

   // Low-g (fall) interrupt enable.
   fI2cSendData(BMA222E_INT_EN_LOW_EN,
                BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_1);
}

/**
 *******************************************************************************
 * @brief disable inturrupt engines to save power
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_DisableIntEngine(void)
{
   //Disable other inturrupt engines
   fI2cSendData(0, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_0);
   fI2cSendData(0, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_1);
   fI2cSendData(0, BMA222E_SLAVE_ADDR, BMA222E_REG_INT_EN_2);

}

/**
 *******************************************************************************
 * @brief Set data range and start free-running acquisition
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_Wake(void)
{
   fI2cSendData(BMA222E_PMU_RANGE_16G, BMA222E_SLAVE_ADDR, BMA222E_REG_PMU_RANGE);
}

/**
 *******************************************************************************
 * @brief Put the BMA222E in a low-power state
 *
 * turns off interrupts and puts the accelerometer into "suspend" mode
 *
 * @param  none
 * @return nothing
 *******************************************************************************
 */
void BMA222E_Suspend(void)
{
   fI2cSendData(BMA222E_PMU_LPW_SUSPEND, BMA222E_SLAVE_ADDR, BMA222E_REG_PMU_LPW);
}

/**
 *******************************************************************************
 * @brief "Getter" for the X axis acceleration
 *
 * @param  none
 * @return Acceleration along the X axis in 2's complement form.  The location
 * of the binary point depends on the selected measurement range.  In the
 * +/- 16g range, there are 6 fractional bits (through the last three are
 * always zero); a change of bit 3 corresponds to a change of 0.125g.
 *******************************************************************************
 */
UINT16 BMA222E_MeasureX(void)
{
   SINT16 val = (SINT8)fI2cGetData(BMA222E_SLAVE_ADDR, BMA222E_REG_ACCD_X_MSB);

   // To use other measurement ranges vary the constant in the RETURN statement as
   // follows to keep the binary point in the same location. This applies equally
   // to the Y & Z axis getter functions.
   //
   // Range   Constant
   // +/-16g      8
   // +/- 8g      4
   // +/- 4g      2
   // +/- 2g      1
   return val * 8;
}

/**
 *******************************************************************************
 * @brief "Getter" for the Y axis acceleration
 *
 * @param  none
 * @return Acceleration along the Y axis in 2's complement form.  The location
 * of the binary point depends on the selected measurement range.  In the
 * +/- 16g range, there are 6 fractional bits (through the last three are
 * always zero); a change of bit 3 corresponds to a change of 0.125g.
 *******************************************************************************
 */
UINT16 BMA222E_MeasureY(void)
{
   SINT16 val = (SINT8)fI2cGetData(BMA222E_SLAVE_ADDR, BMA222E_REG_ACCD_Y_MSB);
   return val * 8;
}

/**
 *******************************************************************************
 * @brief "Getter" for the Z axis acceleration (perpendicular to the PCB)
 *
 * @param  none
 * @return Acceleration along the Z axis in 2's complement form.  The location
 * of the binary point depends on the selected measurement range.  In the
 * +/- 16g range, there are 6 fractional bits (through the last three are
 * always zero); a change of bit 3 corresponds to a change of 0.125g.
 *******************************************************************************
 */
UINT16 BMA222E_MeasureZ(void)
{
   SINT16 val = (SINT8)fI2cGetData(BMA222E_SLAVE_ADDR, BMA222E_REG_ACCD_Z_MSB);
   return val * 8;
}
