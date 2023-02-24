"""Module for testing UOS instruction based commands."""
from pathlib import Path

from packaging.version import parse
from uoshardware.api import UOSDevice


def test_get_firmware_details(test_device: UOSDevice):
    """Confirms the get firmware details returns valid information."""
    response = test_device.get_system_info()
    assert response.status  # Check device responses to the command
    system = response.get_rx_payload(0)
    assert len(system) == 7  # Check payload is correct length
    changelog = Path(__file__).parents[2].joinpath("CHANGES.rst")
    assert changelog.exists()  # Confirm we can find the changelog
    with open(changelog, encoding="utf-8") as changelog_file:
        version = parse(changelog_file.readline().split("Version ")[1])
        assert system[0] == version.micro
        assert system[1] == version.minor
        assert system[2] == version.major
        assert system[3] == 0  # API version LowByte
        assert system[4] == 0  # API version HighByte
        assert system[5] == 1  # Device LowByte
        assert system[6] == 0  # Device HighByte
