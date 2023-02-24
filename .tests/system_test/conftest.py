"""Used to instantiate system-test pytest fixtures."""
import pytest
from uoshardware.api import UOSDevice
from uoshardware.devices import Devices


def pytest_addoption(parser):
    """System test CLI arguments."""
    parser.addoption(
        "--port",
        action="store",
        default=None,
        help="Define the port of the system test device.",
    )


@pytest.fixture()
def test_device(request) -> UOSDevice:
    """Pytest fixture for creating a DUT device for testing with."""
    device_port = request.config.option.port
    if device_port is None:
        pytest.skip(
            "To run the system test suite you must define the "
            "port of the connected device (`--port`)."
        )
    with UOSDevice(
        identity=Devices.arduino_nano,
        address=device_port,
    ) as device:
        yield device
        device.hard_reset()  # Safety incase we do something stupid in the tests.
