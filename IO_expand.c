#include "driver_defines.h"
#include "gpio_port.h"
#include "TM4C123.h"
#include "i2c.h"
#include "IO_expand.h"


//*****************************************************************************
// Reads one byte of data from the current address of the MCP23017  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    data:       data to read.
//
// Returns
// I2C_OK if the byte was written to the MCP23017.
static uint8_t io_expander_read_reg( uint8_t reg_addr)
{
  i2c_status_t status;
	uint8_t data;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {};

  //==============================================================
  // Set the I2C address 
  //==============================================================
	status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
  if ( status != I2C_OK )
  {
    return status;
  }
	
	//==============================================================
  // Write to register address
  //==============================================================
	status = i2cSendByte(IO_EXPANDER_I2C_BASE, reg_addr, I2C_MCS_START | I2C_MCS_RUN);
	if(status != I2C_OK) {
		return status;
	}
	
  //==============================================================
  // Read from register address
  //==============================================================
		status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_READ);
		if(status != I2C_OK) {
			return status;
		}
		status = i2cGetByte( IO_EXPANDER_I2C_BASE, &data , I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
		if ( status != I2C_OK )
		{
			return status;
		}

  return data;
}
//*****************************************************************************
// Writes one byte of data from the current address of the MCP23017  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    data:       data to write.
//
// Returns
// I2C_OK if the byte was written to the MCP23017.
//*****************************************************************************
static uint8_t io_expander_write_reg( uint8_t reg_addr, uint8_t data){
	  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {};

  //==============================================================
  // Set the I2C address to be the io_expander
  //==============================================================
	status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
	if(status != I2C_OK) {
		return status;
	}

  //==============================================================
  // Send register address
  //==============================================================
	status = i2cSendByte(IO_EXPANDER_I2C_BASE, reg_addr, I2C_MCS_START | I2C_MCS_RUN);
	if(status != I2C_OK) {
		return status;
	}
	
  //==============================================================
  // Send send data to write to IO_Expander
  //==============================================================
	status = i2cSendByte(IO_EXPANDER_I2C_BASE, data, I2C_MCS_RUN | I2C_MCS_STOP);
}

bool io_expander_init(void)
{ 
  //==============================
  // Configure I2C GPIO Pins
  //==============================  
  if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN )== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN )== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN )== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
  
  
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(IO_EXPANDER_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
	
	i2cSetSlaveAddr(I2C1_BASE, MCP23017_DEV_ID, I2C_WRITE);
	
  //FOR LEDS
	io_expander_write_reg(MCP23017_IOCONA_R, 0);
	io_expander_write_reg(MCP23017_IODIRA_R, 0);
	
	//pipe pushbuttons to sw2
	//io_expander_write_reg(MCP23017_IODIRB_R, 0x0F);//make pushbuttons to be input
	io_expander_write_reg(MCP23017_IOCONB_R, 0);//make pushbuttons to compare with previous value
	io_expander_write_reg(MCP23017_GPINTENB_R, 0x0F);
	io_expander_write_reg(MCP23017_GPPUB_R, 0x0F);//enable pull-up of pushbuttons
	
	//enable edge-triggering interrupts of all 4 GPIOB pushbutton ports
	if(!gpio_config_falling_edge_irq(GPIOF_BASE, PF0)) return false;
	NVIC_SetPriority(GPIOF_IRQn, 2);
	NVIC_EnableIRQ(GPIOF_IRQn);
	io_expander_read_reg(MCP23017_INTCAPB_R);//read the cap register in every initialization to clear interrupt
	return true;
} 
										
void disableLeds(void) {
	io_expander_write_reg(MCP23017_GPIOA_R, 0x00);
}

void enableLeds(void) {
	io_expander_write_reg(MCP23017_GPIOA_R,0xFF);
}
	
