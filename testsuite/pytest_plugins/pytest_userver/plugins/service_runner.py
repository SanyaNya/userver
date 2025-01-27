# pylint: disable=no-member
import pathlib

import pytest


class UserviceRunner:
    @pytest.hookimpl(tryfirst=True)
    def pytest_collection_modifyitems(self, session, config, items):
        pathes = set()

        # Is there servicetest choosen
        for item in items:
            for marker in item.own_markers:
                if marker.name == 'servicetest':
                    return
                pathes.add(pathlib.Path(item.module.__file__).parent)

        if not pathes:
            return

        tests_root = min(pathes, key=lambda p: len(p.parts))

        module = pytest.Module.from_parent(
            parent=session, path=tests_root / '__service__',
        )
        function = pytest.Function.from_parent(
            parent=module,
            name=test_service_default.__name__,
            callobj=test_service_default,
        )

        items.append(function)


@pytest.mark.servicetest
def test_service_default(service_client):
    """This is default service runner testcase. Feel free to override it
    in your own tests, e.g.:

    @pytest.mark.servicetest
    def test_service(service_client):
        ...
    """


def pytest_configure(config):
    if config.option.service_runner_mode:
        runner = UserviceRunner()
        config.pluginmanager.register(runner, 'uservice_runner')
