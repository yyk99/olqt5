import Map from '../../../../src/ol/Map.js';
import MapBrowserPointerEvent from '../../../../src/ol/MapBrowserPointerEvent.js';
import View from '../../../../src/ol/View.js';
import DragRotateAndZoom from '../../../../src/ol/interaction/DragRotateAndZoom.js';
import VectorLayer from '../../../../src/ol/layer/Vector.js';
import PointerEvent from '../../../../src/ol/pointer/PointerEvent.js';
import VectorSource from '../../../../src/ol/source/Vector.js';

describe('ol.interaction.DragRotateAndZoom', function() {

  describe('constructor', function() {

    it('can be constructed without arguments', function() {
      const instance = new DragRotateAndZoom();
      expect(instance).to.be.an(DragRotateAndZoom);
    });

  });

  describe('#handleDragEvent_()', function() {

    let target, map, interaction;

    const width = 360;
    const height = 180;

    beforeEach(function(done) {
      target = document.createElement('div');
      const style = target.style;
      style.position = 'absolute';
      style.left = '-1000px';
      style.top = '-1000px';
      style.width = width + 'px';
      style.height = height + 'px';
      document.body.appendChild(target);
      const source = new VectorSource();
      const layer = new VectorLayer({source: source});
      interaction = new DragRotateAndZoom();
      map = new Map({
        target: target,
        layers: [layer],
        interactions: [interaction],
        view: new View({
          projection: 'EPSG:4326',
          center: [0, 0],
          resolution: 1
        })
      });
      map.once('postrender', function() {
        done();
      });
    });

    afterEach(function() {
      map.dispose();
      document.body.removeChild(target);
    });

    it('does not rotate when rotation is disabled on the view', function() {
      let event = new MapBrowserPointerEvent('pointermove', map,
        new PointerEvent('pointermove', {clientX: 20, clientY: 10}, {pointerType: 'mouse'}),
        true);
      interaction.lastAngle_ = Math.PI;

      let view = map.getView();
      let spy = sinon.spy(view, 'rotate');
      interaction.handleDragEvent_(event);
      expect(spy.callCount).to.be(1);
      expect(interaction.lastAngle_).to.be(-0.8308214428190254);
      view.rotate.restore();

      view = new View({
        projection: 'EPSG:4326',
        center: [0, 0],
        resolution: 1,
        enableRotation: false
      });
      map.setView(view);

      event = new MapBrowserPointerEvent('pointermove', map,
        new PointerEvent('pointermove', {clientX: 24, clientY: 16}, {pointerType: 'mouse'}),
        true);

      spy = sinon.spy(view, 'rotate');
      interaction.handleDragEvent_(event);
      expect(spy.callCount).to.be(0);
      view.rotate.restore();
    });
  });

});
