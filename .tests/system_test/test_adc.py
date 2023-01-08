"""Module can be used to test adc functionality of an arduino nano DUT."""
from uoshardware.api import UOSDevice


def test_adc_input(test_device: UOSDevice):
    """Checks the 2.5V on A7."""
    assert test_device.get_adc_input(pin=21).status
    reading = test_device.get_pin(pin=21).adc_reading
    assert reading is not None
    if reading is not None:
        assert 2.4 < reading.value < 2.6
