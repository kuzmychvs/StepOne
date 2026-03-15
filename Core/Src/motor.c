#include <motor.h>
#include <main.h>

#define DEFALT_SPEED 800
#define STOP_SPEED 999

uint32_t MotorSpeed = DEFALT_SPEED;

extern TIM_HandleTypeDef htim3;

void Set_Direction(Direction_t direction)
{

	Motor_Deinit();

	switch (direction)
	{
	case forward_m:
		HAL_GPIO_WritePin(GPIOC, GPIO_FL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_FR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BR_Pin, GPIO_PIN_SET);
		break;
	case back_m:
		HAL_GPIO_WritePin(GPIOC, GPIO_FL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_FR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BR_Pin, GPIO_PIN_RESET);
		break;
	case left_m:
		HAL_GPIO_WritePin(GPIOC, GPIO_FL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_FR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BR_Pin, GPIO_PIN_RESET);
		break;
	case right_m:
		HAL_GPIO_WritePin(GPIOC, GPIO_FL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_FR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_BR_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}

	Motor_Init();
}

void Set_motor_Speed(uint32_t MotorSpeed)
{

	TIM3->CCR1 = MotorSpeed; //
	TIM3->CCR2 = MotorSpeed; //
	TIM3->CCR3 = MotorSpeed; //
	TIM3->CCR4 = MotorSpeed; //
}

void Motor1_Set_Speed(uint8_t speedPercent)
{
	uint32_t pwm = (speedPercent * __HAL_TIM_GET_AUTORELOAD(&htim3)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
}

void Motor2_Set_Speed(uint8_t speedPercent)
{
	uint32_t pwm = (speedPercent * __HAL_TIM_GET_AUTORELOAD(&htim3)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm);
}

void Motor3_Set_Speed(uint8_t speedPercent)
{
	uint32_t pwm = (speedPercent * __HAL_TIM_GET_AUTORELOAD(&htim3)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwm);
}

void Motor4_Set_Speed(uint8_t speedPercent)
{
	uint32_t pwm = (speedPercent * __HAL_TIM_GET_AUTORELOAD(&htim3)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
}

void Motor1_SmoothChange(uint8_t current, uint8_t target, uint16_t stepDelayMs)
{
	if (current < target)
	{
		for (uint8_t s = current; s <= target; s++)
		{
			Motor1_Set_Speed(s);
			HAL_Delay(stepDelayMs);
		}
	}
	else
	{
		for (uint8_t s = current; s >= target; s--)
		{
			Motor1_Set_Speed(s);
			HAL_Delay(stepDelayMs);
		}
	}
}

void Motor_Init()
{

	// Set_motor_Speed(DEFALT_SPEED); //

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_Delay(100);
}

void Motor_Deinit()
{

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

	// Set_motor_Speed(STOP_SPEED);

	HAL_Delay(100);
}
