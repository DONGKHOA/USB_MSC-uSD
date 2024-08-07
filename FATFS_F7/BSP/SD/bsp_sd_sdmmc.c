/*
 * bsp_sd_sdmmc.c
 *
 *  Created on: Aug 5, 2024
 *      Author: dongkhoa
 */

/* Includes ------------------------------------------------------------------*/

#include "bsp_sd_def.h"
#include "bsp_sd_sdmmc.h"

/* Extern variables ---------------------------------------------------------*/

extern SD_HandleTypeDef hsd1;

/* Public function ---------------------------------------------------------*/
/**
 * @brief  Initializes the SD card device.
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_Init (void)
{
  uint8_t sd_state = MSD_OK;
  /* Check if the SD card is plugged in the slot */
  if (BSP_SD_SDMMC_IsDetected() != SD_PRESENT)
  {
    return MSD_ERROR_SD_NOT_PRESENT;
  }
  /* HAL SD initialization */
  sd_state = HAL_SD_Init(&hsd1);

  /* Config 4 bit */
  sd_state = HAL_SD_ConfigWideBusOperation(&hsd1, SDMMC_BUS_WIDE_4B);

  return sd_state;
}
/* USER CODE BEGIN AfterInitSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END AfterInitSection */

/* USER CODE BEGIN InterruptMode */
/**
 * @brief  Configures Interrupt mode for SD detection pin.
 * @retval Returns 0
 */
uint8_t
BSP_SD_SDMMC_ITConfig (void)
{
  /* Code to be updated by the user or replaced by one from the FW pack (in a
   * stmxxxx_sd.c file) */

  return (uint8_t)0;
}

/* USER CODE END InterruptMode */

/* USER CODE BEGIN BeforeReadBlocksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeReadBlocksSection */
/**
 * @brief  Reads block(s) from a specified address in an SD card, in polling
 * mode.
 * @param  pData: Pointer to the buffer that will contain the data to transmit
 * @param  ReadAddr: Address from where data is to be read
 * @param  NumOfBlocks: Number of SD blocks to read
 * @param  Timeout: Timeout for read operation
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_ReadBlocks (uint32_t *pData,
                         uint32_t  ReadAddr,
                         uint32_t  NumOfBlocks,
                         uint32_t  Timeout)
{
  uint8_t sd_state = MSD_OK;

  if (HAL_SD_ReadBlocks(&hsd1, (uint8_t *)pData, ReadAddr, NumOfBlocks, Timeout)
      != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/* USER CODE BEGIN BeforeWriteBlocksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeWriteBlocksSection */
/**
 * @brief  Writes block(s) to a specified address in an SD card, in polling
 * mode.
 * @param  pData: Pointer to the buffer that will contain the data to transmit
 * @param  WriteAddr: Address from where data is to be written
 * @param  NumOfBlocks: Number of SD blocks to write
 * @param  Timeout: Timeout for write operation
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_WriteBlocks (uint32_t *pData,
                          uint32_t  WriteAddr,
                          uint32_t  NumOfBlocks,
                          uint32_t  Timeout)
{
  uint8_t sd_state = MSD_OK;

  if (HAL_SD_WriteBlocks(
          &hsd1, (uint8_t *)pData, WriteAddr, NumOfBlocks, Timeout)
      != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/* USER CODE BEGIN BeforeReadDMABlocksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeReadDMABlocksSection */
/**
 * @brief  Reads block(s) from a specified address in an SD card, in DMA mode.
 * @param  pData: Pointer to the buffer that will contain the data to transmit
 * @param  ReadAddr: Address from where data is to be read
 * @param  NumOfBlocks: Number of SD blocks to read
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_ReadBlocks_DMA (uint32_t *pData,
                             uint32_t  ReadAddr,
                             uint32_t  NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;

  /* Read block(s) in DMA transfer mode */
  if (HAL_SD_ReadBlocks_DMA(&hsd1, (uint8_t *)pData, ReadAddr, NumOfBlocks)
      != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/* USER CODE BEGIN BeforeWriteDMABlocksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeWriteDMABlocksSection */
/**
 * @brief  Writes block(s) to a specified address in an SD card, in DMA mode.
 * @param  pData: Pointer to the buffer that will contain the data to transmit
 * @param  WriteAddr: Address from where data is to be written
 * @param  NumOfBlocks: Number of SD blocks to write
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_WriteBlocks_DMA (uint32_t *pData,
                              uint32_t  WriteAddr,
                              uint32_t  NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;

  /* Write block(s) in DMA transfer mode */
  if (HAL_SD_WriteBlocks_DMA(&hsd1, (uint8_t *)pData, WriteAddr, NumOfBlocks)
      != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/* USER CODE BEGIN BeforeEraseSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeEraseSection */
/**
 * @brief  Erases the specified memory area of the given SD card.
 * @param  StartAddr: Start byte address
 * @param  EndAddr: End byte address
 * @retval SD status
 */
uint8_t
BSP_SD_SDMMC_Erase (uint32_t StartAddr, uint32_t EndAddr)
{
  uint8_t sd_state = MSD_OK;

  if (HAL_SD_Erase(&hsd1, StartAddr, EndAddr) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}

/* USER CODE BEGIN BeforeGetCardStateSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeGetCardStateSection */

/**
 * @brief  Gets the current SD card data status.
 * @param  None
 * @retval Data transfer state.
 *          This value can be one of the following values:
 *            @arg  SD_TRANSFER_OK: No data transfer is acting
 *            @arg  SD_TRANSFER_BUSY: Data transfer is acting
 */
uint8_t
BSP_SD_SDMMC_GetCardState (void)
{
  return ((HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER)
              ? SD_TRANSFER_OK
              : SD_TRANSFER_BUSY);
}

/**
 * @brief  Get SD information about specific SD card.
 * @param  CardInfo: Pointer to HAL_SD_CardInfoTypedef structure
 * @retval None
 */
__weak void
BSP_SD_SDMMC_GetCardInfo (HAL_SD_CardInfoTypeDef *CardInfo)
{
  /* Get SD card Information */
  HAL_SD_GetCardInfo(&hsd1, CardInfo);
}

/* USER CODE BEGIN BeforeCallBacksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeCallBacksSection */
/**
 * @brief SD Abort callbacks
 * @param hsd: SD handle
 * @retval None
 */
void
HAL_SD_AbortCallback (SD_HandleTypeDef *hsd)
{
  BSP_SD_SDMMC_AbortCallback();
}

/**
 * @brief Tx Transfer completed callback
 * @param hsd: SD handle
 * @retval None
 */
void
HAL_SD_TxCpltCallback (SD_HandleTypeDef *hsd)
{
  BSP_SD_SDMMC_WriteCpltCallback();
}

/**
 * @brief Rx Transfer completed callback
 * @param hsd: SD handle
 * @retval None
 */
void
HAL_SD_RxCpltCallback (SD_HandleTypeDef *hsd)
{
  BSP_SD_SDMMC_ReadCpltCallback();
}

/* USER CODE BEGIN CallBacksSection_C */
/**
 * @brief BSP SD Abort callback
 * @retval None
 * @note empty (up to the user to fill it in or to remove it if useless)
 */
__weak void
BSP_SD_SDMMC_AbortCallback (void)
{
}

/**
 * @brief BSP Tx Transfer completed callback
 * @retval None
 * @note empty (up to the user to fill it in or to remove it if useless)
 */
__weak void
BSP_SD_SDMMC_WriteCpltCallback (void)
{
}

/**
 * @brief BSP Rx Transfer completed callback
 * @retval None
 * @note empty (up to the user to fill it in or to remove it if useless)
 */
__weak void
BSP_SD_SDMMC_ReadCpltCallback (void)
{
}

/**
 * @brief  Detects if SD card is correctly plugged in the memory slot or not.
 * @param  None
 * @retval Returns if SD is detected or not
 */
uint8_t
BSP_SD_SDMMC_IsDetected (void)
{
  __IO uint8_t status = SD_PRESENT;

  /* USER CODE BEGIN 1 */
  /* user code can be inserted here */
  /* USER CODE END 1 */

  return status;
}
