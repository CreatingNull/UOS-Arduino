"""Module can be used to test gpio functionality of an arduino nano DUT."""
from time import sleep

import pytest
from uoshardware import Persistence
from uoshardware.api import UOSDevice

# Note: See device configuration notes in `TESTS.md`


@pytest.mark.parametrize("volatility", (Persistence.NONE, Persistence.RAM))
def test_gpio_low(volatility: Persistence, test_device: UOSDevice):
    """Checks GPIO signal low for input and output."""
    check_gpio(level=0, volatility=volatility, test_device=test_device)


@pytest.mark.parametrize("volatility", (Persistence.NONE, Persistence.RAM))
def test_gpio_high(volatility: Persistence, test_device: UOSDevice):
    """Checks GPIO signal high for input and output."""
    check_gpio(level=1, volatility=volatility, test_device=test_device)


def test_output_high_to_input_floating(test_device: UOSDevice):
    """Catch the case of switching out high to input to verify
    pull-up is disabled."""
    result = test_device.set_gpio_output(pin=2, level=1)
    assert result.status and len(result.exception) == 0
    sleep(0.5)
    assert test_device.get_gpio_input(pin=5).status  # confirm high
    assert test_device.get_pin(pin=5).gpio_reading is not None
    assert test_device.get_pin(pin=5).gpio_reading.value == 1
    assert test_device.get_gpio_input(pin=2).status
    sleep(5)  # Allow high state to bleed low.
    assert test_device.get_gpio_input(pin=5)
    assert test_device.get_pin(pin=5).gpio_reading is not None
    assert test_device.get_pin(pin=5).gpio_reading.value == 0


@pytest.mark.parametrize("volatility", (Persistence.NONE, Persistence.RAM))
def test_gpio_pull_up_enabled(volatility: Persistence, test_device: UOSDevice):
    """Checks GPIO signal high when set input and pulled up."""
    assert test_device.get_gpio_input(pin=2, pull_up=True, volatility=volatility).status
    assert test_device.get_pin(pin=2).gpio_reading is not None
    assert test_device.get_pin(pin=2).gpio_reading.value == 1
    sleep(0.5)
    # Also confirm this is high on the looped pin.
    for i in range(2):
        assert test_device.get_gpio_input(pin=5).status
        assert test_device.get_pin(pin=5).gpio_reading is not None
        assert test_device.get_pin(pin=5).gpio_reading.value == 1
        if i == 0 and volatility == Persistence.RAM:
            # reset from RAM to confirm result stays the same
            test_device.reset_all_io()
            sleep(0.5)
        else:
            break


def check_gpio(level, volatility: Persistence, test_device: UOSDevice):
    """Verify gpio output level set on pin 2 is measurable on looped back pin 5."""
    # Set pin 2 output high
    assert test_device.set_gpio_output(pin=2, level=level).status
    sleep(0.5)
    # Sample level on tied input 5.
    for i in range(2):
        assert test_device.get_gpio_input(pin=5).status
        assert test_device.get_pin(pin=5).gpio_reading is not None
        assert test_device.get_pin(pin=5).gpio_reading.value == level
        if i == 0 and volatility == Persistence.RAM:
            # reset from RAM to confirm result stays the same.
            test_device.reset_all_io()
            sleep(0.5)
        else:
            break
